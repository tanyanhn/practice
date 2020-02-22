integer function fortran_function(val)
  implicit none
  integer val
  val = val * 3
  fortran_function = 8;
end function fortran_function
