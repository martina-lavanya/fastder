# GTF Output Format

Basic gene annotation 	CHR 	

It contains the basic gene annotation on the reference chromosomes only
This is a subset of the corresponding comprehensive annotation, including only those transcripts tagged as 'basic' in every gene
This is the **main annotation** file for most users


    // MEMBER VARIABLES
    std::string seqname; //name of the chromosome without the "chr" prefix
    std::string source = "fastder";
    std::string feature;
    uint64_t start;
    uint64_t end;
    double score; // the avg coverage of the stitched ER
    std::string strand = ".";
    std::string frame = ".";
    std::string attribute;


have one row per:
    - ER --> exon
    - ER --> transcript
    - ER --> gene


# multi-exon gene with 4 stitched exons

|--| ^ |--| ^ |--| ^ |--|


chr1    fastder   gene        10000   11600   .   +   .   gene_id "geneA"; gene_name "fastder_geneA";
chr1    fastder   transcript  10000   11600   .   +   .   gene_id "geneA"; transcript_id "txA1";
chr1    fastder   exon        10000   10100   .   +   .   gene_id "geneA"; transcript_id "txA1"; exon_number "1";
chr1    fastder   exon        10500   10600   .   +   .   gene_id "geneA"; transcript_id "txA1"; exon_number "2";
chr1    fastder   exon        11000   11100   .   +   .   gene_id "geneA"; transcript_id "txA1"; exon_number "3";
chr1    fastder   exon        11500   11600   .   +   .   gene_id "geneA"; transcript_id "txA1"; exon_number "4";



## Two stitched exons, again in isolation

|--| ^ |--|

Translates to

chr1    fastder   gene        10000   10600   .   +   .   gene_id "gene1"; gene_name "fastder_gene1";
chr1    fastder   transcript  10000   10600   .   +   .   gene_id "gene1"; transcript_id "tx1";
chr1    fastder   exon        10000   10100   .   +   .   gene_id "gene1"; transcript_id "tx1"; exon_number "1";
chr1    fastder   exon        10500   10600   .   +   .   gene_id "gene1"; transcript_id "tx1"; exon_number "2";

weird stuff

16  fastder gene    1347544 1347744 0.614261    .   .   gene_id "gene192"; gene_name "faster_gene192";
16  fastder transcript  1347544 1347744 0.614261    .   .   gene_id "gene192"; transcript_id "tx192";
16  fastder exon    1347544 1347624 0.614261    .   .   gene_id "gene192"; transcript_id "tx192"; exon_number "1";
16  fastder exon    1347624 1347744 0.614261    .   .   gene_id "gene192"; transcript_id "tx192"; exon_number "2";

# notes nov 5th

add part with tolerance for previous ER (often just a gap of 1)



| Splicing Type                             | Description                                                              | Visual Example |    |   |      |   |    |           |    |            |    |         |    |                    |    |   |
| ----------------------------------------- | ------------------------------------------------------------------------ | -------------- | -- | - | ---- | - | -- | --------- | -- | ---------- | -- | ------- | -- | ------------------ | -- | - |
| **Exon Skipping (Cassette Exon)**         | A single exon may be included or skipped.                                | `              | -- | ^ | --   | ^ | -- | `  →  `   | -- | ^        ^ | -- | `       |    |                    |    |   |
| **Multiple Exon Skipping**                | Two or more consecutive exons are skipped together.                      | `              | -- | ^ | --   | ^ | -- | ^         | -- | ^          | -- | `  →  ` | -- | ^                ^ | -- | ` |
| **Intron Retention**                      | An intron remains in the mature mRNA instead of being spliced out.       | `              | -- | ^ | --   | ^ | -- | `  →  `   | -- | ^====^     | -- | `       |    |                    |    |   |
| **Alternative 3′ (Acceptor) Splice Site** | Variable 3′ splice sites change the exon’s downstream boundary.          | `              | -- | ^ | ---- | ^ | -- | `  →  `   | -- | ^          | -- | ^       | -- | `                  |    |   |
| **Alternative 5′ (Donor) Splice Site**    | Variable 5′ splice sites change the exon’s upstream boundary.            | `              | -- | ^ | ---- | ^ | -- | `  →  `   | -- | ^          | -- | ^       | -- | `                  |    |   |
| **Mutually Exclusive Exons**              | Two exons are never included together — only one appears per transcript. | `              | -- | ^ | --   | ^ | -- | `  →  `   | -- | ^          | -- | ^       | -- | `                  |    |   |
| **Alternative First Exon**                | Different transcription start sites lead to alternative first exons.     | `(A)           | -- | ^ | --   | ^ | -- | `<br>`(B) | -- | ^          | -- | ^       | -- | `                  |    |   |
| **Alternative Last Exon**                 | Different polyadenylation sites lead to alternative last exons.          | `              | -- | ^ | --   | ^ | -- | `  →  `   | -- | ^          | -- | ^       | -- | `                  |    |   |


Exon Skipping (Cassette Exon)

Multiple Exon Skipping

Intron Retention

Alternative 3′ (Acceptor) Splice Site

Alternative 5′ (Donor) Splice Site

Mutually Exclusive Exons

Alternative First Exon

Alternative Last Exon


--> see iPad!



# TODOs from 5.11

1. write unit tests for all 4 splicing scenarios to check if my code works.

2. implement such that exon skipping is also recognized

3. quantify how much time is saved by parallelization

4. add --chr and --pos-thr --cov-thr as arguments to parse --> connect --chr with a member variable of Parser

currently, not a single ER is stitched together with another one...

5. for parallelization: maybe allow user spec for #cores, then do #chr / # cores and round down (if 8 / 3 --> 2 cores per chromosome)
