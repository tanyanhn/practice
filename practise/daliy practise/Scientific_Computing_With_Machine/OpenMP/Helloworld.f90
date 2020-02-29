program main

  use omp_lib
  implicit none

  !integer thread_id, thread_count
  !integer OMP_GET_THREAD_NUM
  !OMP_GET_THREAD_NUM = 10
  !$omp parallel
  !private(thread_id, thread_count)
  !integer thread_id, thread_count
  !thread_id = omp_get_thread_num()
  !thread_count = omp_get_num_threads()
  !write (*,*) "Hello from thread number:", thread_id, "out of:" , thread_count
  print *, "Hello I am a thread"
  !$omp end parallel
end program main
