integer function work(val)
  implicit none
  integer val
  write (*,*) "worker ", val , "doing\n"
  work = val * 2
end function work

subroutine work1(val)
  implicit none
  integer val
  write (*,*) "worker ", val , "doing\n"
end subroutine work1



program dofor
  use omp_lib
  implicit none
  integer, external :: work
  integer n, i, return_val, k, count

  n = 11
  !$omp parallel private(k)
  !$omp do
  do i=1,n
     !return_val = work(i)
     call work1(i)
     k = omp_get_thread_num()
     print *, "do for worker k: ", k
     !print *, "work ", i
  end do
  !$omp end do
  k = omp_get_thread_num()
  count = omp_get_num_threads()
  write (*,*) "worker :", k , "out of :", count
  !$omp end parallel

end program dofor

