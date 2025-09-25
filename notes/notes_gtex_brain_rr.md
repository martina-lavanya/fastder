## Notes about the GTEx brain junctions RR file
--> this is across all samples!
chromosome	start	end		length	strand	annotated	left_motif	right_motif	left_annotated											right_annotated
chr1		12698	13203	506		+		0			GT			AG			aC19,gC19,gC24,gC25,gC26,gC29,gC33,kG19,kG38,sG19,sG38	0
chr1		12698	13220	523		+		1			GT			AG			aC19,gC19,gC24,gC25,gC26,gC29,gC33,kG19,kG38,sG19,sG38 aC19,cH38,gC19,gC24,gC25,gC26,gC29,gC33,kG19,kG38,rG19,rG38,sG19,sG38
chr1		12698	13224	527		+		0			GT			AG			aC19,gC19,gC24,gC25,gC26,gC29,gC33,kG19,kG38,sG19,sG38	gC19


describes the chromosome, bp position,


strand: 

   1. + means that the splice junction is on the forward (sense, 5' -> 3') strand of the reference genome (so, the DNA!)
   2. - means that the splice junction is on the reverse (antisense, 3' -> 5') strand of the reference genome (so, the DNA!)

	remember: RNA polymerase always synthesizes RNA in the 5′ → 3′ direction, but it can use **either** DNA strand as the template.


annotation
- both donor and acceptor have to be annotated
	- annotated = 0: the splice junction does not appear in the reference gene models
	- left_annotated and right_annotated:  the donor site (left) or acceptor site (right) matches known exon boundaries in many references of gC (GENCODE version xx)

	remember:
	- Donor Site (5′ Splice Site): This site marks the beginning of an intron and the end of the preceding exon. The most common donor site sequence is GT (GU in pre-mRNA). 
	- Acceptor Site (3′ Splice Site): This site marks the end of an intron and the beginning of the following exon

	so if the left site is annotated but the right is not, this means that we have 

	--------- xxxxx xxxxxxx -------
	exon 1    i1     i2     exon 2

	where either i1 + i2 was the known intron and spliced out before exon 2 (known site) or i1 was the known intron and i2 belonged to exon 2 in the reference annotation

Note: ERCCs (the External RNA Controls Consortium spike-ins) are often added to RNA-seq experiments as artificial control RNAs



# MM file

%%MatrixMarket matrix coordinate integer general
%------------------------------------
9484210	2931	699368828 
	1	2887	1
	1	2068	2
	2	2085	1
	3	1251	1
	3	2064	2
	4	2085	1
	5	2356	1
	6	2065	1

--> 9484210	rows (nr of splice junctions) --> but one splice junction can be on multiple rows if it is mapped by reads of multiple samples
--> 2931 columns (nr of samples)
--> 699368828 (nonzero entries), nr of rows!!
--> third row: how many reads mapped across the junction in sample x

# linking MM and RR
for splice junction id 1, in sample 2887, there was 1 read that mapped to it, and in sample 2068, there were 2 reads that mapped to it

how to map RR files (exon-exon junction coords) to MM files (occurrence of each junction in the 2931 samples)
	--> the RR file has exactly 9484210 junctions, which is also the number of junctions (but not rows) in the market matrix (MM) file!


