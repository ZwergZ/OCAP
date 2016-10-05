#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "ocap_exporter.h"

int i;
int ii;
char *input;
char *output;
char *input_function;
char *input_header1;
char *input_header2;
char *input_line;
static int frame_num = 20000;
static int units_num = 300;
char *filename;


int main() {
	
	printf("Start test\n");
	
	output = malloc(4096);
	
	RVExtension(output, 4096, "version");
	
	for (i=0;i<units_num;i++)
	{
		input_function = "{write;test3.json}";
		input_header1 = "{\"startFrameNum\":0,\"type\":\"unit\",\"id\":0,\"name\":\"Ruslan Chapayev\",\"group\":\"Alpha 1-1\",\"side\":\"EAST\",\"isPlayer\":0\n";
		input_header2 = ",\"positions\":[\n";		
		input_line = "[[123,456],78,9,0],\n";
		
		input = malloc(strlen(input_function) + strlen(input_header1) + strlen(input_header2) + (strlen(input_line) * frame_num) + 1);
		
		strncpy(input, input_function, strlen(input_function));
		strncpy(input + strlen(input_function), input_header1, strlen(input_header1));
		strncpy(input + strlen(input_function) + strlen(input_header1), input_header2, strlen(input_header2));
		
		for (ii=0;ii<frame_num;ii++)
		{
			strncpy(input + strlen(input_function) + strlen(input_header1) + strlen(input_header2) + (strlen(input_line) * ii), input_line, strlen(input_line));
		}
		
		input[strlen(input_function) + strlen(input_header1) + strlen(input_header2) + (strlen(input_line) * frame_num)] = '\0';
		
		RVExtension(output, 4096, input);
		
		free(input);
	}
	
	RVExtension(output, 4096, "{transferLocal;test3.json;x;x;x;http://localhost;/tmp/ocap/;}");
	
	free(output);
	
	printf("End test\n");
	
	return 0;
}