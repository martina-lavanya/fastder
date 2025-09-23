## Notes about the GTEx brain junctions file

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