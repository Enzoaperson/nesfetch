// .NES rom file analyzer by Enzo
#include <stdio.h>

// Fake headers (for testing)
//char header[7] = {'N', 'E', 'S', '.', 2, 1, '\0'}; //Valid
//char header[11] = {'S', 'M', 'S', 'B', 'E', 'T','T','E','R', '\0'}; //Invalid

int main(int argc, char *argv[]){
	
	// Checking if any arguments are passed to the program
	if (argv[1] == NULL){
		printf("Please give me a file to analyze!\n");
		return 0;
	}

     	//Getting the file ready	
	FILE * Nes_Rom;
	char *filename = argv[1];
	Nes_Rom = fopen (argv[1], "rb");

	//Checking if a file is actually being used	
	if (Nes_Rom == NULL) { 		
	   printf("Error: opening ROM file! \n");
	   return 1;
	}

	//Putting the header in memory
	char *header;
	fgets(header, 16, Nes_Rom);

	//Header check
	//The first 4 bytes in an NES ROM File have the values of 78 69 83 26,
	// or NES and the MS-DOS end-of-file value.
	if (header[0]=='N' && header[1]=='E' && header[2]=='S' && header[3]==26){
		printf("File: %s\n", filename);

	    	//ROM Size
	    	printf("ROMS:\n");
	    	printf("	PRG ROM = %d Kib\n", header[4] * 16);
	    	printf("	CHR ROM = %d Kib\n", header[5] * 8);
	    	printf("	Total size = %d Kib\n", header[4] * 16 + header[5] * 8);
	
		//MAPPER
		int mapperid = header[6] >> 4; mapperid += header[7] & 0b11110000; // The first half of this line creates the variable with the lower 4 bits of the mapper ID. The second then adds the upper 4 after bitwise &ing them so that if other bits were set in byte 7 nothing would conflict.
		printf("Mapper:\n");
		printf("	Mapper ID = %d\n", mapperid);

		
		//Other Informtion
		printf("Other:\n");

		//Masks
		int batterymask = 1 << 1;
		int mirrormask = 1;

		//Screen Mirroring
		if(header[6] & mirrormask){
		printf("	Vertically mirrored\n");
		}
		else{
		printf("	Horizontally mirrored (or mapper controlled)\n");
		}
		
		//Battery/Persistent RAM check
		if(header[6] & batterymask){
		printf("	ROM has battery-backed RAM or other persistent memory \n");
		}
		else{
		printf("	ROM has no battery-backed RAM or other persistent memory \n");
		}
		if(mapperid == 20){
		printf("	ROM is a Famicom Disk System ROM \n");
		}

	}else{
    	printf("Error: Not a valid .NES file!\n");
	}
	return 0;
}
