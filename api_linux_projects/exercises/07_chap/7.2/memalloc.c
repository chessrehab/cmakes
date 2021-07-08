//implementation of functions malloc() and free()

//design: program needs to keep a track of free blocks in memory in the form of double linked list: LEGTH:PREVIOUS_BLOCK:NEXT_BLOCK
//malloc0() will check the existing list for a block that has enough room to accomodate requested memory, if it finds it it allocates, if not it will increase the program break and allocate a new block
//free0() will put the freed block to the list of available blocks



#include <stdio.h>
#include <unistd.h>
//sbrk is in unistd.h
#include <string.h>
//memset is in string.h
void *malloc0(size_t);
void free0(void  *);

struct block_t {
	size_t length;
	void *prev_block;
	void *next_block;
};
struct block_t *free_blocks;

size_t *start;

int main(int argc, char *argv[]) {

	free_blocks=(struct block_t *) sbrk(sizeof(struct block_t));
	free_blocks->prev_block=NULL;
	free_blocks->next_block=NULL;
	void *mems[10],*neww;
	char * start_heap=sbrk(0),*loop_ptr,*top_heap;
	int heap_size;
	printf("\n before allocations program break is at  %p",start_heap);
	for (int i=0;i<10;i++) {
		mems[i]=malloc0(i*10);
		memset(mems[i],i,i*10);
		printf("\n after %d. allocation program break is at %p",i,sbrk(0));
	}
	free0(mems[5]);
	neww=malloc0(20);
	memset(neww,69,20);
	top_heap=sbrk(0);	
	heap_size=top_heap-start_heap;
	for(loop_ptr=start_heap;loop_ptr<top_heap;loop_ptr++) {
		printf("%p:%d\n",loop_ptr,*loop_ptr);
	}
	return 0;
	

}

void *malloc0(size_t req_size) {
	void *ptr=free_blocks;
	void *ptr_prev;
	void *result=NULL;
	struct block_t *block_ptr0,*block_ptr1,*block_ptr2;
	int aloc_block_length,free_block_length;
	while(ptr!=NULL) {
		if ((size_t) (((struct block_t*)ptr)->length) >req_size) {
			break;
		}
		ptr_prev=ptr;
		ptr=((struct block_t*) ptr)->next_block;
	}
	if (ptr==NULL) {
		result=sbrk(req_size+sizeof(size_t));	//as there is no available free block big enough, we have to allocate new heap space
		start=(size_t*) result;			//start pointer for new memory

		block_ptr0=(struct block_t *) ptr_prev;	//pointer to previous free block
		block_ptr0->next_block=NULL;		//previous block pointer will become last block in chain

		*start=req_size;			//we fill in the size of allocated memory to the begining of allocated block
		return((void *)start++);	//we return pointer to the allocated memory after the length information
	} else {
		block_ptr0=((struct block_t*) ptr)->prev_block; //we found a block big enough in size so this will be a pointer to the previous block
		block_ptr1=(struct block_t*) ptr;		//pointer to found block to allocate
		block_ptr2=((struct block_t*) ptr)->next_block;  //pointer to next block behind the found block

		free_block_length=sizeof(struct block_t)+block_ptr1->length; //calculate the total length of the found block , including the header
		aloc_block_length=sizeof(size_t)+req_size;		//calculate the total size of allocated block including header

		if((free_block_length-aloc_block_length)>(sizeof(struct block_t))) {		//if there is enough space to create a new free block from leftovers
			block_ptr1=(struct block_t*) (char *) (block_ptr1+1)+block_ptr1->length;  //find the start of the new free block and point 1 to it
			block_ptr0->next_block=(void *)block_ptr1;				//point previous free block's next block pointer to it
			block_ptr1->prev_block=(void *)block_ptr0;				//point previous block pointer of the new free block to the previous block
			block_ptr1->next_block=(void *)block_ptr2;				//point next block pointer of the new free block to the next free block
			block_ptr2->prev_block=(void *)block_ptr1;				//point previous pointer of the next free block to the new free block
		} else {
			block_ptr0->next_block=(void *)block_ptr2;				//if leftover space is not enough to create block, just point previous blocks next block pointer to next free block
			block_ptr2->prev_block=(void *)block_ptr0;				//point previous block pointer of the next free block to the previous free block
		}

		start=(size_t*) ptr;								//point start to the begining of allocated memory
		*start=req_size;								//fill in the length header of the allocated block

		return ((void *)(start+1));							//return pointer to the data part-behind the header
	}
}

void free0(void *ptr) {										//ptr points to memory to be freed
	struct block_t * block_ptr0,*block_ptr1,*block_ptr2,*next_block2;
	char *start,*block_end;
	int block_len2,diff,diff2,length,hole_left,hole_right;

	start=(char *) ptr-sizeof(size_t);							//start points to memory to be freed decreased by size_t size (length header)
	length=*((size_t*) start);								//store length of the memory to be freed
	
	for(block_ptr0=free_blocks;block_ptr0->next_block!=NULL;block_ptr0++) {			//searching for neighbouring free memory block, starting form the begining of chain of free blocks
		if(((void*) block_ptr0)<ptr && ((void*)block_ptr0->next_block)>ptr) break;				//we found the neigbourhood in the free blocks chain, break out of the loop
	}
	block_ptr2=block_ptr0->next_block;							//block_ptr2 now points to neighbour on the right, block_ptr0 points to neighbour to the left
	hole_right=(char*)block_ptr2-(start+sizeof(size_t)+length);		        	//calculate the byte difference in addresess between  start of theneigbour on the right and end of memory chunk to be freed
	block_end=((char*) block_ptr0)+sizeof(struct block_t)+block_ptr0->length;		//block_end points to the end of left neighbour
	hole_left=start-block_end;								//calculate the difference betwwen end of left neigbour block and start of memory chunk to be freed
	if ((hole_left)<=sizeof(struct block_t)) {						//if hole between start of memory chunk to be freed and end of the left neigbour is less than size of the free block header
		block_ptr0->length+=length+sizeof(size_t);					//extend the length of the left neighbour by the whole memory chunk to be freed
	} else {										//there is allocated memory in between the left neighbour and memory chunk to be freed
		if (block_ptr2!=NULL) {								//if we have right neighbour
			if(hole_right<=sizeof(struct block_t)) {				//if the right neighbour is direct neighbour
				next_block2=block_ptr2->next_block;				//save the pointer to the next block of the right neighbour
				block_len2=block_ptr2->length;					//save the length value of the right neighbour
				block_ptr2=(struct block_t*) start;				//move the start of the right neighbour to the start of the memory chunk to be freed
				block_ptr2->next_block=next_block2;				//fill in the header from saved next block pointer
				block_ptr2->prev_block=block_ptr0;				//fill in the header with prev block address (left neighbour)
				block_ptr2->length=block_len2+hole_right+length+sizeof(size_t); //fill in the new length of extended right neighbour
			} else {								//right neighbour is not direct neighbour
				block_ptr1=(struct block_t*) start;				//create a new free memory block from memorychunk to be freed
				block_ptr1->length=length+sizeof(size_t)-sizeof(struct block_t); //fill in the header of the new free block-length
				block_ptr1->prev_block=block_ptr0;				//fill in the header of the new free block-previous block address
				block_ptr1->next_block=block_ptr2;				//fill in the header of the new free block-next block address
			}
		} else {									//there is no right neighbour and the memory chunk to be freed was on top of the heap
			block_ptr1=(struct block_t*) start;					//create a new free block of it (we cannot decrease the heap)
			block_ptr1->length=length+sizeof(size_t)-sizeof(struct block_t);	 //fill in the header of the new free block-length
			block_ptr1->prev_block=block_ptr0;					 //fill in the header of the new free block-previous block
			block_ptr1->next_block=NULL;						 //fill in the header of the new free block-next block, that is NULL as this will be the end of the chain

		}
	}

}

