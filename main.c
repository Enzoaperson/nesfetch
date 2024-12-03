// .NES rom file analyzer
#include <stdio.h>


// Fake headers (for testing)
//char header[7] = {'N', 'E', 'S', '.', 2, 1, '\0'}; //Valid
//char header[11] = {'S', 'M', 'S', 'B', 'E', 'T','T','E','R', '\0'}; //Invalid

int main(int argc, char *argv[]){

     	//Getting the file ready	
	FILE * Nes_Rom;
	char *filename = argv[1];
	Nes_Rom = fopen (argv[1], "rb");	
	if (Nes_Rom == NULL) { //error checking
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
   /*	 
    	// Mapper Section (This will be completed later, so its commented out for now)
    	printf("Mapper:\n");
//    	printf("	Mapper is ");
	printf("%c", header[6]);
	int binaryNumber = 15;
	int bitposition = 3;

	int mask = 1 << bitposition;

	int result = binaryNumber & mask;

	if (result = binaryNumber & mask){
		printf("Bit %d is set.\n", bitposition);
	} else {
		printf("bit %d is not set.\n", bitposition);
	}
	

/*	
    	switch (binaryNumber){
		case 1: puts("Mapper1");
//        	default: puts ("Unknown Mapper");
*/ 
		printf("Other:\n");

		//Masks
		int batterymask = 1 << 1;
		int mirrormask = 1;

		if(header[6] & mirrormask){
		printf("	Horizontal mirrored\n");
		}
		else{
		printf("	Vertically mirrored (or mapper controlled)\n");
		}

		if(header[6] & batterymask){
		printf("	ROM has battery-backed RAM or other persistent memory \n");
		}
		else{
		printf("	ROM has no battery-backed RAM or other persistent memory \n");
		}


	//File is not valid .NES file
	}else{
    	printf("Error: Not a valid .NES file!\n");
	}
	return 0;
}

