subroutine work1(val)
  implicit none
  integer val
  write (*,*) "worker ", val , "doing\n"
end subroutine work1

integer function work(val)
  implicit none
  integer val
  write (*,*) "worker ", val , "doing\n"
  work = val
end function work


program dofor
  implicit none
  integer, external :: work
  integer i, n, return_val
  real a(10)
  real t1, t2
  n = 11

  !$omp parallel do private(t1, t2), &
  !$omp shared(a)
  do i=1,n
     !call work1(i)
     !return_val = work(i)
     t1 = work(i)
     t2 = work(i)
     a(i) = sqrt(t1 ** 2 + t2 ** 2)
  end do
  !$omp end parallel do
  n = 10
  !$omp parallel do
  do i=1,11
     write (*,*) "a(" , i, ") is ", a(i)
  end do
  !$omp end parallel do
end program dofor
