/*
 * ocap_exporter.c
 */
#include <string.h>     // strcmp, strncpy
#include <stdio.h>
#include <stdlib.h>
 
void RVExtension(char *output, int outputSize, const char *function)
{
	static char version[] = "1.0";
	char *arg[8];
	char *option;
    char *captureFilename;
	char *worldName;
    char *missionName;
    char *missionDuration;
    char *postUrl;
    char *webRoot; // Must include trailing '/'
	const char *start_arg;
	const char *end_arg;
	const char *end;
	char *text;
	char *file_path;
	char *file_path_dest;
	int arg_index;
	int arg_num; 
	int arg_len;
	int text_len;
	FILE *file;
	
    printf("OCAP EXP: ");
	
	if (!strcmp(function, "version"))
    {
        strncpy(output, version, outputSize);
    }
	else
	{	
		if (function[0] == '{')
		{
			arg_num = 0;		
			start_arg = function + 1;
			end = strstr(start_arg, "}");
			end_arg = start_arg;
			if (end)
			{
				while(end_arg != end)
				{
					end_arg = strstr(start_arg, ";");
					
					if (!end_arg) end_arg = end;
					
					arg_len = end_arg - start_arg;
					
					arg[arg_num] = malloc(arg_len + 1);					
					strncpy(arg[arg_num], start_arg, arg_len);
					arg[arg_num][arg_len] = '\0';
					printf("A%d:%s ", arg_num, arg[arg_num]);	
					
					arg_num++;
					start_arg = end_arg + 1;
				}
				
				if (*(end + 1) != '\0')
				{
					text_len = strlen(end + 1);
					
					text = malloc(text_len + 1);
					strncpy(text, end + 1, text_len);
					text[text_len] = '\0';
					printf("T:%d", strlen(text));	
				}
				
				// TODO: Implementierung der eigentlichen Funktion
				
				option = arg[0];
				captureFilename = arg[1];
				
				file_path = malloc(strlen(captureFilename)+5+1);
				strncpy(file_path, "/tmp/", 5);
				strncpy(file_path+5, captureFilename, strlen(captureFilename));
				file_path[strlen(captureFilename)+5] = '\0';
				
				if (strcmp(option, "write")==0)
				{
//					printf("%s \n", file_path);
					file = fopen(file_path, "a");
					if (file!=NULL)
					{
						fputs (text,file);
						fclose (file);
					}
					free(text);
					strncpy(output, "OK: Write successfull.", outputSize);
				}
				else if (strcmp(option, "transferLocal")==0 || strcmp(option, "transferRemote")==0)
				{
					worldName = arg[2];
					missionName = arg[3];
					missionDuration = arg[4];
					postUrl = arg[5];
					//postUrl += "data/receive.php";
					webRoot = arg[6]; // Must include trailing '/'
                    //transferFilepath = webRoot + "data/" + captureFilename;
					
					printf(" wN:%s mN:%s mD:%s pU:%s",worldName, missionName, missionDuration, postUrl);
					
					if (strcmp(option, "transferLocal")==0)
					{
						file_path_dest = malloc(strlen(captureFilename)+strlen(webRoot)+1);
						strncpy(file_path_dest, webRoot, strlen(webRoot));
						strncpy(file_path_dest+strlen(webRoot), captureFilename, strlen(captureFilename));
						file_path_dest[strlen(captureFilename)+strlen(webRoot)] = '\0';
						rename(file_path, file_path_dest);
						free(file_path_dest);
					}
					else
					{
						//string ftpHost = args[6];
						//string ftpUsername = args[7];
						//string ftpPassword = args[8];	
						strncpy(output, "ERROR: transferRemote is not implemented yet.", outputSize);
					}
					
					//TODO: Send HTTP POST Request to tell to the Web Server, that a new file exists
					
					strncpy(output, "OK: Transfer successfull.", outputSize);
				}
				else
				{
					strncpy(output, "ERROR: Funktion not allowed.", outputSize);
				}
				
				for (arg_index=0;arg_index<arg_num;arg_index++)
				{
					free(arg[arg_index]);
				}
				free(file_path);
			}
			else
			{
				strncpy(output, "ERROR: End of function missed.", outputSize);
			}
		} 
		else
		{
			strncpy(output, "ERROR: Start of function misssed.", outputSize);
		}
	}
	printf(">>>%s", output);
	printf("\n");
    return;
}