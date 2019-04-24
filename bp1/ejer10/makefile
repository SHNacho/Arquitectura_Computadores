GXX=gcc -O2 -fopenmp

all: SumaVectoresC_for_mod SumaVectoresC_sections_mod SumaVectoresC_mod

SumaVectoresC_for_mod : SumaVectoresC_for_mod.c
	$(GXX) SumaVectoresC_for_mod.c -o $@

SumaVectoresC_sections_mod : SumaVectoresC_for_mod.c
	$(GXX) SumaVectoresC_sections_mod.c -o $@

SumaVectoresC_mod : SumaVectoresC_for_mod.c
	$(GXX) SumaVectoresC_mod.c -o $@
	
clean: 
	rm -f SumaVectoresC_for_mod SumaVectoresC_sections_mod SumaVectoresC_mod
