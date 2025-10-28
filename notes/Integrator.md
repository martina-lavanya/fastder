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
