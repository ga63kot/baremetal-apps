
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <optimsoc-baremetal.h>

struct trace_packet{
	uint16_t size;
	uint16_t event_id;
	uint32_t timestamp;
	uint16_t n_args;
	uint32_t args[];
};

int main() {

	struct trace_packet diagnosis_results;

	int *packet_available = (int*) 0xFE800004; //pointer to check if there is a packet available
	int *run_queue = (int*) 0xFE800008; //pointer to read address of next packet in ready queue
	int *discard_queue = (int*) 0xFE800004; //pointer to write address of last packet read
	int *config = (int*) 0xFE000000; //pointer to configuration registers for Debug Units

	uint32_t initial_trace_address;

	//*config = 0x00000002; //size
	//*(config+1) = 0x00007a3c; //conf reg addr
	//*(config+2) = 0x00002424; //value
	//*(config+3) = 0x00000002; //size
	//*(config+4) = 0x00007a40; //conf reg addr
	//*(config+5) = 0x00000000; //value
	//*(config+6) = 0x00000002; //size
	//*(config+7) = 0x00007a44; //conf reg addr
	//*(config+8) = 0x00008001; //value

	//*(config+9) = 0x00000002;  //size
	//*(config+10) = 0x00007a84; //conf reg addr
	//*(config+11) = 0x00000800; //value
	//*(config+12) = 0x00000002; //size
	//*(config+13) = 0x00007a88; //conf reg addr
	//*(config+14) = 0x00000000; //value
	//*(config+15) = 0x00000002; //size
	//*(config+16) = 0x00007a8c; //conf reg addr
	//*(config+17) = 0x00008001; //value

	  *discard_queue = 0x00000000; //previous address to starting of preserved memory space for trace data

	while(1) {

	  //if the flag is active means that there is a new packet ready
		initial_trace_address = *run_queue;

		if (initial_trace_address != 0xFFFFFFFF) {
			//store initial address of trace packet
			//initial_trace_address = *run_queue;
			uint32_t* current_packet = (uint32_t*) initial_trace_address;

			//size is in first address of packet
			diagnosis_results.size = *current_packet;
			//printf("SIZE = %u\n", diagnosis_results.size);

			//event ID is in second address of packet
			diagnosis_results.event_id = (*(current_packet+1)&(0x0000003F));
			printf("EVENT_ID = %u\n", diagnosis_results.event_id);

			//timestamp is in third address of packet
			diagnosis_results.timestamp = *(current_packet+2);
			printf("TIMESTAMP = %#010x\n", diagnosis_results.timestamp);

			//calculate number of arguments in trace packet
			diagnosis_results.n_args = (diagnosis_results.size-4)/2;
			//printf("N_ARGS = %u\n", diagnosis_results.n_args);

			//loop for reading all args and store them from consecutive addresses
			int i;
			for (i=0; i<diagnosis_results.n_args; i++) {
				//printf("i = %u\n", i);
				uint32_t arg_address = current_packet + 3 + i;
				uint32_t* arg = (uint32_t*) arg_address;
				printf("ARG%u = %#010x\n", i+1, *arg);
			}
			printf("-------------------------\n");
			//place packet in discard queue
			*discard_queue = initial_trace_address + (4*diagnosis_results.size)/2;
		}
  }

}
