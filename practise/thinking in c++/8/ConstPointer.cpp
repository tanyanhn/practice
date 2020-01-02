//constant pointer arg/return
void t(int*){}

void u(const int* cip){
	//!  *cip = 2;  //Illegal -- modifies value
	 int i = *cip;  //OK -- copies value
	//!  int* ip2 = cip;  //Illegal: non-const
}

const char* v(){
	//Returns address of static character array:
	return "result of function v()";
}

const int* const w(){
	static int i;
	return &i;
} 

int main() {
	int x = 0;
	int* ip = &x;
	const int* cip = &x;
	t(ip);  //OK
	//! t(cip); 
	u(ip);
	//!char* cp = v();
	const char* cpp = v();
	//!int* ip2 = w();
	const int* const cci = w();
	const int* cip2 = w();
	//!*w() = 1;
}
