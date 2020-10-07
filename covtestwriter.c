#include <stdio.h>
#include "giftcard.h"

struct this_gift_card examplegc_1;
struct this_gift_card examplegc_2;
struct gift_card_data examplegcd_1;
struct gift_card_data examplegcd_2;
struct gift_card_record_data examplegcrd_1;
struct gift_card_amount_change examplegcac;
struct gift_card_record_data examplegcrd_2;
struct gift_card_program examplegcp; 

void setupgc(){
	examplegc_1.num_bytes = 120;
	examplegc_1.gift_card_data = (void *) &examplegcd_1;
	examplegc_2.num_bytes = 500;
	examplegc_2.gift_card_data = (void *) &examplegcd_2;
	examplegcd_1.merchant_id = "1234567890";
	examplegcd_2.merchant_id = "1234567890";
	examplegcd_1.customer_id = "1234567890";
	examplegcd_2.customer_id = "1234567890";
	examplegcd_1.number_of_gift_card_records = 1;
	examplegcd_2.number_of_gift_card_records = 1;

	examplegcd_1.gift_card_record_data = malloc(40);
	examplegcd_2.gift_card_record_data = malloc(400);
	examplegcd_1.gift_card_record_data[0] = (void *) &examplegcrd_1;
	examplegcd_2.gift_card_record_data[0] = (void *) &examplegcrd_2;
	examplegcrd_1.record_size_in_bytes = 40;
	examplegcrd_1.type_of_record = 2;
        examplegcrd_1.actual_record = (void *) &examplegcac;
        examplegcac.amount_added = 1000;
        examplegcac.actual_signature = "[Wilson Li]";	
	examplegcrd_2.record_size_in_bytes = 320;
	examplegcrd_2.type_of_record = 3;
	examplegcrd_2.actual_record = (void *) &examplegcp;
	//char message[32] = {0};
	//strcpy(message,"this is just testing"); 
}

void writegc(){
	FILE *fd1;
	FILE *fd2;
	fd1 = fopen("crash_test_1.gft","w");
	fwrite(&examplegc_1.num_bytes,4,1,fd1);
	fwrite(examplegcd_1.merchant_id,32,1,fd1);
	fwrite(examplegcd_1.customer_id,32,1,fd1);
	fwrite(&examplegcd_1.number_of_gift_card_records,4,1,fd1);
	fwrite(&examplegcrd_1.record_size_in_bytes,4,1,fd1);
	fwrite(&examplegcrd_1.type_of_record,4,1,fd1);
	fwrite(examplegcac.actual_signature,32,1,fd1);
	fclose(fd1);
	fd2 = fopen("hang_real.gft","w");
	fwrite(&examplegc_2.num_bytes,4,1,fd2);
	fwrite(examplegcd_2.merchant_id,32,1,fd2);
	fwrite(examplegcd_2.customer_id,32,1,fd2);
	fwrite(&examplegcd_2.number_of_gift_card_records,4,1,fd2);
	fwrite(&examplegcrd_2.record_size_in_bytes,4,1,fd2);
	fwrite(&examplegcrd_2.type_of_record,4,1,fd2);
	char message[32] = {0};
	strcpy(message,"this is just testing");
	fwrite(message,32,1,fd2);
	/*unsigned char program[256] = {
		0x01, 0x00, 0x00, //getchar r0
		0x04, 0x20, 0x01, //mov r1,0x20
		0x05, 0x00, 0x01, // xor r0,r1
		0x02, 0x00, 0x00, // putchar r0
		0x07, 0x00, 0x00, // print
		0x03, 0x01, 0x00, // movchar +1
	};*/
	unsigned char crash_program[256] = {
		0x09, -3, 0x00,
	};
	fwrite(crash_program,256,1,fd2);
	fclose(fd2);
}

int main(void) {
	setupgc();
	writegc();
	return 0;
}
