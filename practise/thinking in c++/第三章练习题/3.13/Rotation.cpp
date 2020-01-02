unsigned char rol(unsigned char val){
	int highbit;
	if(val & 0x80)
	  highbit= 1;
	else
	  highbit= 0;
	  
	val <<=1;
	val |= highbit;
	return val;
}
unsigned char ror(unsigned char val){
		int lowbit;
	if(val & 1)
	  lowbit= 1;
	else
	  lowbit= 0;
	  
	val >>=1;
	val |= (lowbit << 7);
	return val;
}
