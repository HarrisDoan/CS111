//605317270 Harris Doan CS111 Lab2

#include <errno.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

typedef uint32_t u32;
typedef int32_t i32;

struct process
{
  u32 pid;
  u32 arrival_time;
  u32 burst_time;

  TAILQ_ENTRY(process) pointers;

  /* Additional fields here */
  u32 time_start;
  u32 time_remaining;
  bool start_flag;
  /* End of "Additional fields here" */
};

TAILQ_HEAD(process_list, process);

u32 next_int(const char **data, const char *data_end)
{
  u32 current = 0;
  bool started = false;
  while (*data != data_end)
  {
    char c = **data;

    if (c < 0x30 || c > 0x39)
    {
      if (started)
      {
        return current;
      }
    }
    else
    {
      if (!started)
      {
        current = (c - 0x30);
        started = true;
      }
      else
      {
        current *= 10;
        current += (c - 0x30);
      }
    }

    ++(*data);
  }

  printf("Reached end of file while looking for another integer\n");
  exit(EINVAL);
}

u32 next_int_from_c_str(const char *data)
{
  char c;
  u32 i = 0;
  u32 current = 0;
  bool started = false;
  while ((c = data[i++]))
  {
    if (c < 0x30 || c > 0x39)
    {
      exit(EINVAL);
    }
    if (!started)
    {
      current = (c - 0x30);
      started = true;
    }
    else
    {
      current *= 10;
      current += (c - 0x30);
    }
  }
  return current;
}

void init_processes(const char *path,
                    struct process **process_data,
                    u32 *process_size)
{
  int fd = open(path, O_RDONLY);
  if (fd == -1)
  {
    int err = errno;
    perror("open");
    exit(err);
  }

  struct stat st;
  if (fstat(fd, &st) == -1)
  {
    int err = errno;
    perror("stat");
    exit(err);
  }

  u32 size = st.st_size;
  const char *data_start = mmap(NULL, size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (data_start == MAP_FAILED)
  {
    int err = errno;
    perror("mmap");
    exit(err);
  }

  const char *data_end = data_start + size;
  const char *data = data_start;

  *process_size = next_int(&data, data_end);

  *process_data = calloc(sizeof(struct process), *process_size);
  if (*process_data == NULL)
  {
    int err = errno;
    perror("calloc");
    exit(err);
  }

  for (u32 i = 0; i < *process_size; ++i)
  {
    (*process_data)[i].pid = next_int(&data, data_end);
    (*process_data)[i].arrival_time = next_int(&data, data_end);
    (*process_data)[i].burst_time = next_int(&data, data_end);
    (*process_data)[i].start_flag = false;
    (*process_data)[i].time_remaining = (*process_data)[i].burst_time;
  }

  munmap((void *)data, size);
  close(fd);
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    return EINVAL;
  }
  struct process *data;
  u32 size;
  init_processes(argv[1], &data, &size);

  u32 quantum_length = next_int_from_c_str(argv[2]);

  struct process_list list;
  TAILQ_INIT(&list);

  u32 total_waiting_time = 0;
  u32 total_response_time = 0;

  /* Your code here */
  struct process_list ready_queue;
  TAILQ_INIT(&ready_queue);

  u32 accumulated_waiting_time = 0;
  u32 accumulated_response_time = 0;

  /* Sorting processes by arrival time and PID */
  for (u32 idx = 0; idx < size; idx++)
  {
    struct process* proc = &data[idx]; // Use the allocated array directly
    TAILQ_INSERT_TAIL(&ready_queue, proc, pointers);
  }

  u32 current_time = 0;
  struct process_list process_queue;
  TAILQ_INIT(&process_queue);
  struct process* current_process = NULL;

  /* Process scheduling loop */
  while(!(TAILQ_EMPTY(&process_queue) && TAILQ_EMPTY(&ready_queue) && current_process == NULL))
  {
    struct process *next_process, *selected_process;
    while((next_process = TAILQ_FIRST(&ready_queue)) && next_process->arrival_time <= current_time)
    {
      TAILQ_REMOVE(&ready_queue, next_process, pointers);
      TAILQ_INSERT_TAIL(&process_queue, next_process, pointers);
    }

    if(current_process)
    {
      TAILQ_INSERT_TAIL(&process_queue, current_process, pointers);
      current_process = NULL;
    }

    if((selected_process = TAILQ_FIRST(&process_queue)))
    {
      TAILQ_REMOVE(&process_queue, selected_process, pointers);
      if(!selected_process->start_flag)
      {
        selected_process->start_flag = true;
        accumulated_response_time += current_time - selected_process->arrival_time;
      }

      u32 work_time = selected_process->time_remaining < quantum_length ? selected_process->time_remaining : quantum_length;
      selected_process->time_remaining -= work_time;
      current_time += work_time;

      if(selected_process->time_remaining == 0)
      {
        accumulated_waiting_time += current_time - selected_process->arrival_time - selected_process->burst_time;
      }
      else
      {
        current_process = selected_process;
      }
    }
    else
    {
      current_time++;
    }
  }
  total_waiting_time = accumulated_waiting_time;
  total_response_time = accumulated_response_time;
  /* End of "Your code here" */

  printf("Average waiting time: %.2f\n", (float)total_waiting_time / (float)size);
  printf("Average response time: %.2f\n", (float)total_response_time / (float)size);

  free(data);
  return 0;
}
