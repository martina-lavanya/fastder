# INTEGRATOR OVERVIEW


# TODOs 20.10
- think about if i want to iterate over expressed_regions first and just define iterator over mm_sj_counts?
- think if I want to include stitch_up in StitchedER function anyway? but where to store stitched_ERs, it needs a class of its own.
- keep working in Integrator.cpp stitch_up function

EXPRESSED REGIONS

chrom	start	end		coverage total_reads length

chr19	60826	60900	0.307075	0	74
chr19	61541	61551	0.287577	0	10
chr19	63950	64021	0.320889	0	71
chr19	405526	405595	0.285235	0	69
chr19	405620	405625	0.303309	0	5
chr19	405638	405646	0.286046	0	8
chr19	405734	406391	0.342137	0	657
chr19	406520	406533	0.280511	0	13
chr19	406535	406791	0.305104	0	256
chr19	407195	407214	0.271614	0	19
chr19	416694	417321	0.459661	0	627
chr19	418922	419055	0.444365	0	133
chr19	422145	422455	0.417054	0	310
chr19	425096	425227	0.331935	0	131
chr19	430696	430746	0.306984	0	50
chr19	434708	434743	0.307444	0	35
chr19	434767	434779	0.277287	0	12
chr19	434817	434864	0.296016	0	47
chr19	436164	436290	0.321285	0	126
chr19	436379	436430	0.328327	0	51

SPLICE JUNCTIONS

chr19	60748	64413	3666	0	0	CT	AC	gC19	0
chr19	60748	71430	10683	0	0	CT	AC	gC19	gC19
chr19	60981	61016	36	1	0	GT	AG	0	0
chr19	61228	61294	67	0	0	CT	AC	0	0
chr19	64214	65338	1125	0	0	CT	AC	aC19,gC19,gC24,gC25,gC26,gC29,gC33,kG38,sG19	0
chr19	66617	70927	4311	0	0	CT	AC	0	aC19,cH38,gC19,gC24,gC25,gC26,gC29,gC33,kG19,kG38,lR19,lR38,rG19,rG38,sG19,sG38
chr19	66849	68554	1706	0	0	CT	GC	0	0
chr19	71103	71430	328	0	0	CT	AC	0	gC19
chr19	71124	71430	307	0	0	CT	AC	0	gC19
chr19	115669	143353	27685	0	0	CT	AC	0	0
chr19	120029	191185	71157	0	0	CT	AC	0	aC19,gC24,gC25,gC26,gC29,gC33,kG38,sG19,sG38
chr19	191404	195503	4100	0	0	CT	AC	0	gC24,gC25,gC26,gC29,gC33,kG38,sG19,sG38
chr19	195699	203870	8172	0	0	CT	AC	0	aC19,cH38,gC24,gC25,gC26,gC29,gC33,kG38
chr19	198229	198283	55	0	0	CT	AC	0	0
chr19	198336	200523	2188	1	0	GC	AG	0	0
chr19	198548	199223	676	0	0	CT	AC	gC19	sG19,sG38
chr19	198645	200390	1746	0	0	CT	AC	0	cH38,gC24,gC25,gC26,gC29,gC33,kG38,sG19,sG38
chr19	198742	199904	1163	0	0	CT	AC	0	cH38
chr19	198765	198895	131	1	0	GT	AG	0	0
chr19	198839	199758	920	0	0	CT	AC	0	cH38

what kind of a sequence does mm_sj_counts have? what will mm_sj_counts.begin() even give me?
- 
Alternatively, I’m happy to reply to Mr. Deceuninck to explain that I had misunderstood the visitor status application process and that the current application he sent is fine as is.

think about why SJ from other chromosomes than 19 were added?? is fill_up() in parser working correctly? 

--> because mm_sj_counts uses the rail_id to check for splice junctions and therefore adds splice junctions of ALL chromosomes, and so far I was only using chromosome 19 files.

# TODO 21.10

- problem: when running on server, it cannot count any splice junctions 

	nr of splice junctions across all samples in user input: 0


but when running on local machine in CLION, I get 334231 junctions for
	../data/gtex.base_sums.BRAIN_GTEX-Q2AG-2926-SM-2HMJ3.1.ALL.bedGraph
	../data/gtex.base_sums.BRAIN_GTEX-15SHU-3126-SM-6M46H.1.ALL.bedGraph

	I get 20075 junctions for only chromosome 19

- also, what is the sequence of the mm_sj_counts file? is it ordered by chromosome and bp position as it should be and as it is in the RR file?

# TODO change type of mm_sj_counts to something that preserves order of RR file!!


# question why can one stitched ER contain the expresse regions of non-sequential er_ids?
it cannot, they have to be sequential. but the print statements only show the ones with more than one ER in them, so some er_ids are not printed



weird sig segv error 

lR38,rG19,rG38,sG19,sG38	aC19,cH38,gC19,gC24,gC25,gC26,gC29,gC33,kG19,kG38,lR19,lR38,rG19,rG38,sG19,sG38chr2	242130813	242175168	44356	1	0	GT	AG	aC19,cH38,gC19,gC24,gC25,gC26,gC29,gC33,kG38,lR19,lR38,rG19,rG38,sG19,sG38	sG38chr2	242130813	242175168	44356	1	0	GT	AG	aC19,cH38,gC19,gC24,gC25,gC26,gC29,gC33,kG38,lR19,lR38,rG19,rG38,sG19,sG38	sG38chr2	242130867	242159348	28482	1	0	GT	AG	aC19,gC19,gC24,gC25,gC26,gC29,gC33,kG38,lR19,lR38,sG19,sG38	aC19,cH38,gC19,gC24,gC25,gC26,gC29,gC33,kG19,kG38,lR19,lR38,rG19,rG38,sG19,sG38chr2	242130867	242159348	28482	1	0	GT	AG	aC19,gC19,gC24,gC25,gC26,gC29,gC33,kG38,lR19,lR38,sG19,sG38	aC19,cH38,gC19,gC24,gC25,gC26,gC29,gC33,kG19,kG38,lR19,lR38,rG19,rG38,sG19,sG38chr2	242161423	242161481	59	1	0	GT	AG	0	0chr2	242162835	242162976	142	1	0	GT	AG	0	0chr2	242162984	242163058	75	1	0	GT	AG	0	0chr2	242163502	242163556	55	1	0	GC	AG	0	0chr2	242163774	242163796	23	1	0	AT	AC	0	0chr2	242163774	242163796	23	1	0	AT	AC	0	0chr2	242164868	242164888	21	1	0	GC	AG	0	0chr2	242164868	242164888	21	1	0	GC	AG	0	0chr2	242166799	242167050	252	1	0	GT	AG	aC19,sG19,sG38	0chr2	242166799	242167050	252	1	0	GT	AG	aC19,sG19,sG38	0chr2	242167094	242167189	96	1	1	GT	AG	aC19,sG19,sG38	aC19,sG19,sG38chr2	242167098	242172559	5462	1	0	GT	AG	0	0chr2	242167405	242172559	5155	1	0	GT	AG	0	0chr2	24
Process finished with exit code 139 (interrupted by signal 11:SIGSEGV)


further print statements show that it first reads 

issue was that i was also only parsing permitted lines of the RR file but the RR file should have all of the SJ in it --> the IDE stopped it because it kept generating the same print statement for a null lookup of rr[sj_id]

--> removed chr_permitted() from RR file now

if this finishes running now including stitch_up() which kept quitting, perhaps cause i was using cached mm file rather than the mm file with only the splice junctions from chr 1 and 2


# UPDATE 28.10
running for the following files:
	gtex.base_sums.BRAIN_GTEX-1HBPH-3126-SM-9WYUV.1.ALL.bedGraph
	gtex.base_sums.BRAIN_GTEX-YFC4-3126-SM-5PNV6.1.ALL.bedGraph

and the following chromosomes
	chromosome 1 + 2

nr of splice junctions across all samples in user input: 10998

#samples = 2, #chromosomes = 2
4481 expressed regions

number of stitched regions = 1050
max_stitched_ers = 22


nr of splice junctions across all samples in user input: 31327
FINISHED PARSING
#samples = 2, #chromosomes = 1
 first 20 out of 4608 expressed regions
max_stitched_ers = 40
stitched ER index	(length,average coverage)
stitched_er.across_er_coverage	stitched_er.start	stitched_er.end	stitched_er.total_length
number of stitched regions = 2106



# for chromosome 1
4608 expressed regions
number of stitched regions = 4381
nr of sj in provided data + permitted chromosomes = 31327

# for chromosomes 1 + 2
4481 expressed regions
number of stitched regions = 2647
nr of sj in provided data + permitted chromosomes = 31327

4481 expressed regions
number of stitched regions = 2647
nr of sj in provided data + permitted chromosomes = 31327
splice junctions in chr 1: 31327
splice junctions in chr 2: 0
expressed regions in chr 1: 2769
expressed regions in chr 2: 1712
stitched regions in chr 1: 2645
stitched regions in chr 2: 2


# for chromosome 2
4965 expressed regions, 
nr of sj in provided data + permitted chromosomes = 0
the first sj_id is from an ERCC chromosome, how did this even happen?

# TODO 28.10: 
- implement custom sorting of chromosomes: think about where I need this / where I rely on the chromosomes being in order, since mm_sj_counts will be in order (but only with the permitted chromosomes)
	-> examples are the mean_coverage vector

- there is a bug in which sj_id are added to mm_sj_count!! find out what it is
	malformed line in MM file: 3917031 --> problem was that not the entire MM file was downloaded.



# TODO 29.10:
- think about if the SJ id and chromosomes are really matched.


# tolerance: 3 bp

max_stitched_ers = 2
stitched ER index	(length,average coverage)
stitched_er.across_er_coverage	stitched_er.start	stitched_er.end	stitched_er.total_length
4517 expressed regions
number of stitched regions = 1813
nr of sj in provided data + permitted chromosomes = 64668
splice junctions in chr 1: 31327
splice junctions in chr 9: 14277
splice junctions in chr 19: 19064
expressed regions in chr 1: 1833
expressed regions in chr 9: 874
expressed regions in chr 19: 1810
stitched regions in chr 1: 1811
stitched regions in chr 9: 2
stitched regions in chr 19: 0



# tolerance 5 bp, only chr 19

max_stitched_ers = 2
stitched ER index	(length,average coverage)
stitched_er.across_er_coverage	stitched_er.start	stitched_er.end	stitched_er.total_length
5101 expressed regions
number of stitched regions = 4899
nr of sj in provided data + permitted chromosomes = 19064
only chr 1 actually stitched chromosomes, there must still be a bug


max_stitched_ers = 2
stitched ER index	(length,average coverage)
stitched_er.across_er_coverage	stitched_er.start	stitched_er.end	stitched_er.total_length
4517 expressed regions
number of stitched regions = 1793
nr of sj in provided data + permitted chromosomes = 64668
splice junctions in chr 1: 31327
splice junctions in chr 9: 14277
splice junctions in chr 19: 19064
expressed regions in chr 1: 1833
expressed regions in chr 9: 874
expressed regions in chr 19: 1810
stitched regions in chr 1: 1791
stitched regions in chr 9: 2
stitched regions in chr 19: 0


4517 expressed regions
number of stitched regions = 1793
nr of sj in provided data + permitted chromosomes = 64668
splice junctions in chr 1: 31327
splice junctions in chr 9: 14277
splice junctions in chr 19: 19064
expressed regions in chr 1: 1833
expressed regions in chr 9: 874
expressed regions in chr 19: 1810
stitched regions in chr 1: 1791
stitched regions in chr 9: 0
stitched regions in chr 19: 2



# TO IZASKUN

I also wanted to ask what offset tolerance of exon end position and splice junction start position I should use. I am currently working with 5bp, but technically there shouldn't be more than +- 2-3bp of noise and even 1 bp causes a frame shift. I haven't found any guidelines about this in literature. I did find this paper which states that alternative splice sites can be as little as 3 bp apart ("acceptor splice sites, i.e., alternative acceptor sites that are located 3 bp apart from each other", https://journals.plos.org/ploscompbiol/article?id=10.1371%2Fjournal.pcbi.1008329). What do you think? 



# SORTING

there is no requirement for mean_coverage or expressed_regions to be ordered by chromosome!

mm_sj_counts is ordered by sj_id size, BUT the corresponding info in rr_all_sj is not ordered (but it is grouped by) chromosome
-> sj_ids are ordered by chromosome position within a chromosome




# Chromosome length in human genome
	
Total length (bp)
	
GenBank accession
	
RefSeq accession
1 	248,956,422 	CM000663.2 	NC_000001.11
2 	242,193,529 	CM000664.2 	NC_000002.12
3 	198,295,559 	CM000665.2 	NC_000003.12
4 	190,214,555 	CM000666.2 	NC_000004.12
5 	181,538,259 	CM000667.2 	NC_000005.10
6 	170,805,979 	CM000668.2 	NC_000006.12
7 	159,345,973 	CM000669.2 	NC_000007.14
8 	145,138,636 	CM000670.2 	NC_000008.11
9 	138,394,717 	CM000671.2 	NC_000009.12
10 	133,797,422 	CM000672.2 	NC_000010.11
11 	135,086,622 	CM000673.2 	NC_000011.10
12 	133,275,309 	CM000674.2 	NC_000012.12
13 	114,364,328 	CM000675.2 	NC_000013.11
14 	107,043,718 	CM000676.2 	NC_000014.9
15 	101,991,189 	CM000677.2 	NC_000015.10
16 	90,338,345 		CM000678.2 	NC_000016.10
17 	83,257,441 		CM000679.2 	NC_000017.11
18 	80,373,285 		CM000680.2 	NC_000018.10
19 	58,617,616 		CM000681.2 	NC_000019.10
20 	64,444,167 		CM000682.2 	NC_000020.11
21 	46,709,983 		CM000683.2 	NC_000021.9
22 	50,818,468 		CM000684.2 	NC_000022.11
X 	156,040,895 	CM000685.2 	NC_000023.11
Y 	57,227,415 		CM000686.2 	NC_000024.10



# TODOs 29.10

- make mm_sj_counts chromosome specific as well! maybe just store the chromosome and a vector of the sj_ids rather than the sj_ids and a vector of the counts!! --> only changed parser class so far


last run: 

max_stitched_ers = 0
stitched ER index	(length,average coverage)
stitched_er.across_er_coverage	stitched_er.start	stitched_er.end	stitched_er.total_length
number of stitched regions = 5189
nr of sj in provided data + permitted chromosomes = 37272
splice junctions in chr chr21 = 3654
splice junctions in chr chr19 = 17793
splice junctions in chr chr16 = 15825
expressed regions in chr chr21 = 302
expressed regions in chr chr19 = 3065
expressed regions in chr chr16 = 1863
stitched ERs in chr chr21 = 303
stitched ERs in chr chr19 = 3066
stitched ERs in chr chr16 = 1820

number of stitched regions = 5085
splice junctions in chr chr16 = 24814
splice junctions in chr chr19 = 28188
splice junctions in chr chr21 = 5667
expressed regions in chr chr21 = 302
expressed regions in chr chr19 = 3065
expressed regions in chr chr16 = 1863
stitched ERs in chr chr21 = 299
stitched ERs in chr chr19 = 2966
stitched ERs in chr chr16 = 1820


max_stitched_ers = 0
number of stitched regions = 5233
splice junctions in chr chr16 = 24814
splice junctions in chr chr19 = 28188
splice junctions in chr chr21 = 5667
expressed regions in chr chr21 = 302
expressed regions in chr chr19 = 3065
expressed regions in chr chr16 = 1863
stitched ERs in chr chr21 = 303
stitched ERs in chr chr19 = 3066
stitched ERs in chr chr16 = 1864


max_stitched_ers = 0
number of stitched regions = 5233
splice junctions in chr chr16 = 24814
splice junctions in chr chr19 = 28188
splice junctions in chr chr21 = 5667
expressed regions in chr chr21 = 302
expressed regions in chr chr19 = 3065
expressed regions in chr chr16 = 1863
stitched ERs in chr chr21 = 303
stitched ERs in chr chr19 = 3066
stitched ERs in chr chr16 = 1864