program fortran_program
  implicit none
  integer, external :: fortran_function
  integer, external :: c_function
  integer, external :: cpp_function
  integer, external :: cpp_class_method_wrapper;
  integer::val;
  integer::return_val
  val = 1;

  print *, "Running Fortran program with val = ", val
  return_val = fortran_function(val)
  print *, "fortran_function returns val = ", val
  print *, "fortran_function returns return_val = ", return_val
  return_val = c_function(val);
  print *, "c_function returns val = ", val
  print *, "c_function returns return_val = ", return_val
  return_val = cpp_function(val);
  print*,"cpp_function returns val = ", val
  print *, "cpp_function returns return_val = ", return_val
  return_val = cpp_class_method_wrapper(val);
  print *, "cpp_class_method_wrapper returns val = ", val;
  print *, "cpp_class_method_wrapper returns return_val = ", return_val
  print *, "Fortran program complete."
  print *, ""
end program fortran_program