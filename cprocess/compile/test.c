#include<stdio.h>

#define NUMBER 69

int a=10;
int b;
FILE f;
FILE *xtra34;
const char* basic="0123456789abcdef";
fpos_t pos;
int q;
void dump() {
	
	printf("--------------------------------------------\n");
	printf("--------------------------------------------\n");
	printf ("_IO_read_ptr       :%p\n",xtra34->_IO_read_ptr);
	printf ("_IO_read_end       :%p\n",xtra34->_IO_read_end);
	printf ("_IO_read_base      :%p\n",xtra34->_IO_read_base);
	printf("--------------------------------------------\n");
	printf ("_IO_write_base     :%p\n",xtra34->_IO_write_base);
	printf ("_IO_write_ptr      :%p\n",xtra34->_IO_write_ptr);
	printf ("_IO_write_end      :%p\n",xtra34->_IO_write_end);
	printf("--------------------------------------------\n");
	printf ("_IO_save_base      :%p\n",xtra34->_IO_save_base);
	printf ("_IO_backup_base    :%p\n",xtra34->_IO_backup_base);
	printf ("_IO_save_end       :%p\n",xtra34->_IO_save_end);
	printf("--------------------------------------------\n");
	printf ("_IO_buf_base       :%p\n",xtra34->_IO_buf_base);
	printf ("_IO_buf_end        :%p\n",xtra34->_IO_buf_end);
	printf("--------------------------------------------\n");
	printf ("_fileno            :%d\n",xtra34->_fileno);
	printf ("_old_offset        :%d\n",(int) xtra34->_old_offset);
	printf ("_cur_column        :%d\n",xtra34->_cur_column);
	printf ("_shortbuf          :%c\n",xtra34->_shortbuf[0]);
	printf ("_offset            :%d\n",(int)xtra34->_offset);
	printf("--------------------------------------------\n");
}

int main() {
	int c=123,number=NUMBER;
	char d ='x';
	
	xtra34=fopen("test2","r+");
	int i=getc(xtra34);
	int i2=getc(xtra34);
	int i3=getc(xtra34);
	q=fgetpos(xtra34,&pos);
	dump();
	printf("\n currently at pos:%d\n",(int) pos.__pos);
	
	int p=putc('m',xtra34);
	printf("\n return:%d\n",p);
	fflush(xtra34);
	dump();
	q=fgetpos(xtra34,&pos);
	printf("\n currently at pos:%d\n",(int) pos.__pos);
	int i4=getc(xtra34);
	dump();
	q=fgetpos(xtra34,&pos);
	printf("\n currently at pos:%d\n",(int) pos.__pos);
	rewind(xtra34);
	q=fgetpos(xtra34,&pos);
	printf("\n currently at pos:%d\n",(int) pos.__pos);
	fputs(basic,xtra34);
	fclose(xtra34);
	printf("\nsize of f:%d\n",(int)sizeof(f));
	
	return 0;


}
