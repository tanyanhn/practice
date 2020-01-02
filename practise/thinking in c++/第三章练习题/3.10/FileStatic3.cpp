extern int fs;

void func(){
	fs=100;
}
static int fs;

int main(){
	fs=1;
}
