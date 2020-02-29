subroutine work1(val)
  implicit none
  integer val
  write (*,*) "worker ", val , "doing\n"
end subroutine work1

integer function work(val)
  implicit none
  integer val
  write (*,*) "worker ", val , "doing\n"
  work = val * 2
end function work


program dofor
  implicit none
  integer, external :: work
  integer i, n, return_val
  n = 11

  !$omp parallel do
  do i=1,n
     !call work1(i)
     return_val = work(i)
  end do
  !$omp end parallel do
end program dofor
