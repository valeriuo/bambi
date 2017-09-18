/*  test/i2b/i2b.c -- i2b test cases.

    Copyright (C) 2016 Genome Research Ltd.

    Author: Jennifer Liddle <js10@sanger.ac.uk>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#include <config.h>

#include "bambi.h"
#include "../src/i2b.c"
#include <stdlib.h>
#include <unistd.h>

#define xMKNAME(d,f) #d f
#define MKNAME(d,f) xMKNAME(d,f)

int verbose = 0;

const char * bambi_version(void)
{
    return "12.34";
}

int success = 0;
int failure = 0;

void setup_param_test(int* argc, char*** argv)
{
    *argc = 0;
    *argv = (char**)calloc(sizeof(char*), 100);
    (*argv)[(*argc)++] = strdup("bambi");
    (*argv)[(*argc)++] = strdup("i2b");
    (*argv)[(*argc)++] = strdup("-i");
    (*argv)[(*argc)++] = strdup(MKNAME(DATA_DIR,"/160916_miseq_0966_FC/Data/Intensities"));
    (*argv)[(*argc)++] = strdup("-o");
    (*argv)[(*argc)++] = strdup("test/data/out/xxx.sam");
    (*argv)[(*argc)++] = strdup("--output-fmt");
    (*argv)[(*argc)++] = strdup("sam");
    (*argv)[(*argc)++] = strdup("--lane");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--first-tile");
    (*argv)[(*argc)++] = strdup("1101");
    (*argv)[(*argc)++] = strdup("--tile-limit");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--library-name");
    (*argv)[(*argc)++] = strdup("testlibrary");
    (*argv)[(*argc)++] = strdup("--run-folder");
    (*argv)[(*argc)++] = strdup(MKNAME(DATA_DIR,"/160916_miseq_0966_FC/"));
    (*argv)[(*argc)++] = strdup("--study-name");
    (*argv)[(*argc)++] = strdup("teststudy");
    (*argv)[(*argc)++] = strdup("--basecalls-dir");
    (*argv)[(*argc)++] = strdup(MKNAME(DATA_DIR,"/160916_miseq_0966_FC/Data/Intensities/BaseCalls/"));
    (*argv)[(*argc)++] = strdup("--generate-secondary-basecalls");
    (*argv)[(*argc)++] = strdup("--no-filter");
    (*argv)[(*argc)++] = strdup("--sequencing-centre");
    (*argv)[(*argc)++] = strdup("XY");
    (*argv)[(*argc)++] = strdup("--platform");
    (*argv)[(*argc)++] = strdup("Illumina");
    (*argv)[(*argc)++] = strdup("--first-tile");
    (*argv)[(*argc)++] = strdup("1103");
    (*argv)[(*argc)++] = strdup("--tile-limit");
    (*argv)[(*argc)++] = strdup("5");
    (*argv)[(*argc)++] = strdup("--barcode-tag");
    (*argv)[(*argc)++] = strdup("AB");
    (*argv)[(*argc)++] = strdup("--quality-tag");
    (*argv)[(*argc)++] = strdup("CD");
    (*argv)[(*argc)++] = strdup("--sec-barcode-tag");
    (*argv)[(*argc)++] = strdup("WX");
    (*argv)[(*argc)++] = strdup("--sec-quality-tag");
    (*argv)[(*argc)++] = strdup("YZ");
    (*argv)[(*argc)++] = strdup("--bc-read");
    (*argv)[(*argc)++] = strdup("2");
    (*argv)[(*argc)++] = strdup("--first-cycle");
    (*argv)[(*argc)++] = strdup("7");
    (*argv)[(*argc)++] = strdup("--first-cycle");
    (*argv)[(*argc)++] = strdup("17");
    (*argv)[(*argc)++] = strdup("--first-cycle");
    (*argv)[(*argc)++] = strdup("70");
    (*argv)[(*argc)++] = strdup("--final-cycle");
    (*argv)[(*argc)++] = strdup("16");
    (*argv)[(*argc)++] = strdup("--final-cycle");
    (*argv)[(*argc)++] = strdup("69");
    (*argv)[(*argc)++] = strdup("--final-cycle");
    (*argv)[(*argc)++] = strdup("70");
    (*argv)[(*argc)++] = strdup("--first-index-cycle");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--final-index-cycle");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("-s");

    assert(*argc<100);
}

void setup_simple_test(int* argc, char*** argv, char *outputfile, bool verbose)
{
    *argc = 0;
    *argv = (char**)calloc(sizeof(char*), 100);
    (*argv)[(*argc)++] = strdup("bambi");
    (*argv)[(*argc)++] = strdup("i2b");
    (*argv)[(*argc)++] = strdup("-i");
    (*argv)[(*argc)++] = strdup(MKNAME(DATA_DIR,"/160916_miseq_0966_FC/Data/Intensities"));
    (*argv)[(*argc)++] = strdup("-o");
    (*argv)[(*argc)++] = strdup(outputfile);
    (*argv)[(*argc)++] = strdup("--lane");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--first-tile");
    (*argv)[(*argc)++] = strdup("1101");
    (*argv)[(*argc)++] = strdup("--tile-limit");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--library-name");
    (*argv)[(*argc)++] = strdup("Test library");
    (*argv)[(*argc)++] = strdup("--sample-alias");
    (*argv)[(*argc)++] = strdup("Test Sample");
    (*argv)[(*argc)++] = strdup("--study-name");
    (*argv)[(*argc)++] = strdup("Study testStudy");
    (*argv)[(*argc)++] = strdup("--run-start-date");
    (*argv)[(*argc)++] = strdup("2011-03-23T00:00:00+0000");
    if (verbose) (*argv)[(*argc)++] = strdup("--verbose");

    assert(*argc<100);
}

void setup_readgroup_test(int* argc, char*** argv, char *outputfile, bool verbose)
{
    *argc = 0;
    *argv = (char**)calloc(sizeof(char*), 100);
    (*argv)[(*argc)++] = strdup("bambi");
    (*argv)[(*argc)++] = strdup("i2b");
    (*argv)[(*argc)++] = strdup("-i");
    (*argv)[(*argc)++] = strdup(MKNAME(DATA_DIR,"/160916_miseq_0966_FC/Data/Intensities"));
    (*argv)[(*argc)++] = strdup("-o");
    (*argv)[(*argc)++] = strdup(outputfile);
    (*argv)[(*argc)++] = strdup("--lane");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--first-tile");
    (*argv)[(*argc)++] = strdup("1101");
    (*argv)[(*argc)++] = strdup("--tile-limit");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--library-name");
    (*argv)[(*argc)++] = strdup("Test library");
    (*argv)[(*argc)++] = strdup("--sample-alias");
    (*argv)[(*argc)++] = strdup("Test Sample");
    (*argv)[(*argc)++] = strdup("--study-name");
    (*argv)[(*argc)++] = strdup("Study testStudy");
    (*argv)[(*argc)++] = strdup("--run-start-date");
    (*argv)[(*argc)++] = strdup("2011-03-23T00:00:00+0000");
    if (verbose) (*argv)[(*argc)++] = strdup("--verbose");
    (*argv)[(*argc)++] = strdup("--read-group-id");
    (*argv)[(*argc)++] = strdup("6000_1");

    assert(*argc<100);
}

void setup_cyclerange_test(int* argc, char*** argv, char *outputfile, bool verbose)
{
    *argc = 0;
    *argv = (char**)calloc(sizeof(char*), 100);
    (*argv)[(*argc)++] = strdup("bambi");
    (*argv)[(*argc)++] = strdup("i2b");
    (*argv)[(*argc)++] = strdup("-i");
    (*argv)[(*argc)++] = strdup(MKNAME(DATA_DIR,"/160919_hiseqx_0557_FC/Data/Intensities"));
    (*argv)[(*argc)++] = strdup("-o");
    (*argv)[(*argc)++] = strdup(outputfile);
    (*argv)[(*argc)++] = strdup("--lane");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--first-tile");
    (*argv)[(*argc)++] = strdup("1101");
    (*argv)[(*argc)++] = strdup("--tile-limit");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--library-name");
    (*argv)[(*argc)++] = strdup("TestLibrary");
    (*argv)[(*argc)++] = strdup("--sample-alias");
    (*argv)[(*argc)++] = strdup("TestSample");
    (*argv)[(*argc)++] = strdup("--study-name");
    (*argv)[(*argc)++] = strdup("Study TestStudy");
    (*argv)[(*argc)++] = strdup("--run-start-date");
    (*argv)[(*argc)++] = strdup("2011-03-23T00:00:00+0000");
    if (verbose) (*argv)[(*argc)++] = strdup("--verbose");
    (*argv)[(*argc)++] = strdup("--first-cycle");
    (*argv)[(*argc)++] = strdup("6");
    (*argv)[(*argc)++] = strdup("--final-cycle");
    (*argv)[(*argc)++] = strdup("10");

    assert(*argc<100);
}

void setup_bcread_test(int* argc, char*** argv, char *outputfile, bool verbose)
{
    *argc = 0;
    *argv = (char**)calloc(sizeof(char*), 100);
    (*argv)[(*argc)++] = strdup("bambi");
    (*argv)[(*argc)++] = strdup("i2b");
    (*argv)[(*argc)++] = strdup("-i");
    (*argv)[(*argc)++] = strdup(MKNAME(DATA_DIR,"/160919_nextseq_6230_FC/Data/Intensities"));
    (*argv)[(*argc)++] = strdup("-o");
    (*argv)[(*argc)++] = strdup(outputfile);
    (*argv)[(*argc)++] = strdup("--lane");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--first-tile");
    (*argv)[(*argc)++] = strdup("11101");
    (*argv)[(*argc)++] = strdup("--tile-limit");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--library-name");
    (*argv)[(*argc)++] = strdup("TestLibrary");
    (*argv)[(*argc)++] = strdup("--sample-alias");
    (*argv)[(*argc)++] = strdup("TestSample");
    (*argv)[(*argc)++] = strdup("--study-name");
    (*argv)[(*argc)++] = strdup("Study TestStudy");
    (*argv)[(*argc)++] = strdup("--run-start-date");
    (*argv)[(*argc)++] = strdup("2011-03-23T00:00:00+0000");
    if (verbose) (*argv)[(*argc)++] = strdup("--verbose");
    (*argv)[(*argc)++] = strdup("--first-cycle");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--final-cycle");
    (*argv)[(*argc)++] = strdup("2");
    (*argv)[(*argc)++] = strdup("--first-cycle");
    (*argv)[(*argc)++] = strdup("15");
    (*argv)[(*argc)++] = strdup("--final-cycle");
    (*argv)[(*argc)++] = strdup("19");
    (*argv)[(*argc)++] = strdup("--first-index-cycle");
    (*argv)[(*argc)++] = strdup("30");
    (*argv)[(*argc)++] = strdup("--final-index-cycle");
    (*argv)[(*argc)++] = strdup("31");
    (*argv)[(*argc)++] = strdup("--bc-read");
    (*argv)[(*argc)++] = strdup("2");

    assert(*argc<100);
}

void setup_dualindex_test(int* argc, char*** argv, char *outputfile, bool verbose)
{
    *argc = 0;
    *argv = (char**)calloc(sizeof(char*), 100);
    (*argv)[(*argc)++] = strdup("bambi");
    (*argv)[(*argc)++] = strdup("i2b");
    (*argv)[(*argc)++] = strdup("-i");
    (*argv)[(*argc)++] = strdup(MKNAME(DATA_DIR,"/160919_hiseq4000_7984_FC/Data/Intensities"));
    (*argv)[(*argc)++] = strdup("-o");
    (*argv)[(*argc)++] = strdup(outputfile);
    (*argv)[(*argc)++] = strdup("--lane");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--first-tile");
    (*argv)[(*argc)++] = strdup("1101");
    (*argv)[(*argc)++] = strdup("--tile-limit");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--library-name");
    (*argv)[(*argc)++] = strdup("TestLibrary");
    (*argv)[(*argc)++] = strdup("--sample-alias");
    (*argv)[(*argc)++] = strdup("TestSample");
    (*argv)[(*argc)++] = strdup("--study-name");
    (*argv)[(*argc)++] = strdup("Study TestStudy");
    (*argv)[(*argc)++] = strdup("--run-start-date");
    (*argv)[(*argc)++] = strdup("2011-03-23T00:00:00+0000");
    if (verbose) (*argv)[(*argc)++] = strdup("--verbose");
    (*argv)[(*argc)++] = strdup("--no-filter");
    (*argv)[(*argc)++] = strdup("--barcode-tag");
    (*argv)[(*argc)++] = strdup("tr");
    (*argv)[(*argc)++] = strdup("--quality-tag");
    (*argv)[(*argc)++] = strdup("tq");
    (*argv)[(*argc)++] = strdup("--sec-barcode-tag");
    (*argv)[(*argc)++] = strdup("BC");
    (*argv)[(*argc)++] = strdup("--sec-quality-tag");
    (*argv)[(*argc)++] = strdup("QT");

    assert(*argc<100);
}

void setup_tags_test(int* argc, char*** argv, char *outputfile, bool verbose)
{
    *argc = 0;
    *argv = (char**)calloc(sizeof(char*), 100);
    (*argv)[(*argc)++] = strdup("bambi");
    (*argv)[(*argc)++] = strdup("i2b");
    (*argv)[(*argc)++] = strdup("-i");
    (*argv)[(*argc)++] = strdup(MKNAME(DATA_DIR,"/160919_hiseq2500_4966_FC/Data/Intensities"));
    (*argv)[(*argc)++] = strdup("-o");
    (*argv)[(*argc)++] = strdup(outputfile);
    (*argv)[(*argc)++] = strdup("--lane");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--first-tile");
    (*argv)[(*argc)++] = strdup("1101");
    (*argv)[(*argc)++] = strdup("--tile-limit");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--library-name");
    (*argv)[(*argc)++] = strdup("TestLibrary");
    (*argv)[(*argc)++] = strdup("--sample-alias");
    (*argv)[(*argc)++] = strdup("TestSample");
    (*argv)[(*argc)++] = strdup("--study-name");
    (*argv)[(*argc)++] = strdup("Study TestStudy");
    (*argv)[(*argc)++] = strdup("--run-start-date");
    (*argv)[(*argc)++] = strdup("2011-03-23T00:00:00+0000");
    if (verbose) (*argv)[(*argc)++] = strdup("--verbose");
    (*argv)[(*argc)++] = strdup("--first-cycle");
    (*argv)[(*argc)++] = strdup("1,30");
    (*argv)[(*argc)++] = strdup("--final-cycle");
    (*argv)[(*argc)++] = strdup("2,32");
    (*argv)[(*argc)++] = strdup("--first-index-cycle");
    (*argv)[(*argc)++] = strdup("3,6,11");
    (*argv)[(*argc)++] = strdup("--final-index-cycle");
    (*argv)[(*argc)++] = strdup("5,10,12");
    (*argv)[(*argc)++] = strdup("--barcode-tag");
    (*argv)[(*argc)++] = strdup("b1,b2,b3");
    (*argv)[(*argc)++] = strdup("--quality-tag");
    (*argv)[(*argc)++] = strdup("q1,q2,q3");

    assert(*argc<100);
}

void separator_test(int* argc, char*** argv, char *outputfile, bool verbose)
{
    *argc = 0;
    *argv = (char**)calloc(sizeof(char*), 100);
    (*argv)[(*argc)++] = strdup("bambi");
    (*argv)[(*argc)++] = strdup("i2b");
    (*argv)[(*argc)++] = strdup("-i");
    (*argv)[(*argc)++] = strdup(MKNAME(DATA_DIR,"/160919_hiseq2500_4966_FC/Data/Intensities"));
    (*argv)[(*argc)++] = strdup("-o");
    (*argv)[(*argc)++] = strdup(outputfile);
    (*argv)[(*argc)++] = strdup("--lane");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--first-tile");
    (*argv)[(*argc)++] = strdup("1101");
    (*argv)[(*argc)++] = strdup("--tile-limit");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--library-name");
    (*argv)[(*argc)++] = strdup("TestLibrary");
    (*argv)[(*argc)++] = strdup("--sample-alias");
    (*argv)[(*argc)++] = strdup("TestSample");
    (*argv)[(*argc)++] = strdup("--study-name");
    (*argv)[(*argc)++] = strdup("Study TestStudy");
    (*argv)[(*argc)++] = strdup("--run-start-date");
    (*argv)[(*argc)++] = strdup("2011-03-23T00:00:00+0000");
    if (verbose) (*argv)[(*argc)++] = strdup("--verbose");
    (*argv)[(*argc)++] = strdup("--first-cycle");
    (*argv)[(*argc)++] = strdup("1,30");
    (*argv)[(*argc)++] = strdup("--final-cycle");
    (*argv)[(*argc)++] = strdup("2,32");
    (*argv)[(*argc)++] = strdup("--first-index-cycle");
    (*argv)[(*argc)++] = strdup("3,6,11");
    (*argv)[(*argc)++] = strdup("--final-index-cycle");
    (*argv)[(*argc)++] = strdup("4,9,12");
    (*argv)[(*argc)++] = strdup("--barcode-tag");
    (*argv)[(*argc)++] = strdup("b1,b2,b1");
    (*argv)[(*argc)++] = strdup("--quality-tag");
    (*argv)[(*argc)++] = strdup("q1,q2,q1");
    (*argv)[(*argc)++] = strdup("-s");

    assert(*argc<100);
}

void no_separator_test(int* argc, char*** argv, char *outputfile, bool verbose)
{
    *argc = 0;
    *argv = (char**)calloc(sizeof(char*), 100);
    (*argv)[(*argc)++] = strdup("bambi");
    (*argv)[(*argc)++] = strdup("i2b");
    (*argv)[(*argc)++] = strdup("-i");
    (*argv)[(*argc)++] = strdup(MKNAME(DATA_DIR,"/160919_hiseq2500_4966_FC/Data/Intensities"));
    (*argv)[(*argc)++] = strdup("-o");
    (*argv)[(*argc)++] = strdup(outputfile);
    (*argv)[(*argc)++] = strdup("--lane");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--first-tile");
    (*argv)[(*argc)++] = strdup("1101");
    (*argv)[(*argc)++] = strdup("--tile-limit");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--library-name");
    (*argv)[(*argc)++] = strdup("TestLibrary");
    (*argv)[(*argc)++] = strdup("--sample-alias");
    (*argv)[(*argc)++] = strdup("TestSample");
    (*argv)[(*argc)++] = strdup("--study-name");
    (*argv)[(*argc)++] = strdup("Study TestStudy");
    (*argv)[(*argc)++] = strdup("--run-start-date");
    (*argv)[(*argc)++] = strdup("2011-03-23T00:00:00+0000");
    if (verbose) (*argv)[(*argc)++] = strdup("--verbose");
    (*argv)[(*argc)++] = strdup("--first-cycle");
    (*argv)[(*argc)++] = strdup("1,30");
    (*argv)[(*argc)++] = strdup("--final-cycle");
    (*argv)[(*argc)++] = strdup("2,32");
    (*argv)[(*argc)++] = strdup("--first-index-cycle");
    (*argv)[(*argc)++] = strdup("3,6,11");
    (*argv)[(*argc)++] = strdup("--final-index-cycle");
    (*argv)[(*argc)++] = strdup("4,9,12");
    (*argv)[(*argc)++] = strdup("--barcode-tag");
    (*argv)[(*argc)++] = strdup("b1,b2,b1");
    (*argv)[(*argc)++] = strdup("--quality-tag");
    (*argv)[(*argc)++] = strdup("q1,q2,q1");

    assert(*argc<100);
}

void novaseq_test(int* argc, char*** argv, char *outputfile, bool verbose)
{
    *argc = 0;
    *argv = (char**)calloc(sizeof(char*), 100);
    (*argv)[(*argc)++] = strdup("bambi");
    (*argv)[(*argc)++] = strdup("i2b");
    (*argv)[(*argc)++] = strdup("-i");
    (*argv)[(*argc)++] = strdup(MKNAME(DATA_DIR,"/novaseq/Data/Intensities"));
    (*argv)[(*argc)++] = strdup("-o");
    (*argv)[(*argc)++] = strdup(outputfile);
    (*argv)[(*argc)++] = strdup("--lane");
    (*argv)[(*argc)++] = strdup("1");
    (*argv)[(*argc)++] = strdup("--no-filter");
    (*argv)[(*argc)++] = strdup("--library-name");
    (*argv)[(*argc)++] = strdup("TestLibrary");
    (*argv)[(*argc)++] = strdup("--sample-alias");
    (*argv)[(*argc)++] = strdup("TestSample");
    (*argv)[(*argc)++] = strdup("--study-name");
    (*argv)[(*argc)++] = strdup("Study TestStudy");
    (*argv)[(*argc)++] = strdup("--run-start-date");
    (*argv)[(*argc)++] = strdup("2011-03-23T00:00:00+0000");
    if (verbose) (*argv)[(*argc)++] = strdup("--verbose");

    assert(*argc<100);
}

void free_args(char **argv)
{
    for (int n=0; n<100; n++) free(argv[n]);
    free(argv);
}

void checkLike(char *name, char *expected, char *actual)
{
    if (actual == NULL) actual = "<null>";
    if (strstr(actual, expected) == NULL) {
        fprintf(stderr, "%s\n" "Expected: %s\n" "Got:      %s\n", name, expected, actual);
        failure++;
    }
}

void checkEqual(char *name, char *expected, char *actual)
{
    if (actual == NULL) actual = "<null>";
    if (strcmp(expected, actual)) {
        fprintf(stderr, "%s\n" "Expected: %s\n" "Got:      %s\n", name, expected, actual);
        failure++;
    }
}

void icheckEqual(char *name, int expected, int actual)
{
    if (expected != actual) {
        fprintf(stderr, "%s\n" "Expected: %d\n" "Got:      %d\n", name, expected, actual);
        failure++;
    }
}

void test_paramaters(void)
{
    // minimal options
    int argc_1;
    char** argv_1;
    setup_param_test(&argc_1, &argv_1);
    opts_t *opts = i2b_parse_args(argc_1-1, argv_1+1);

    if (verbose) printf("Testing paramaters\n");

    if (!opts) {
        fprintf(stderr, "parse_args failed\n");
        failure++;
        return;
    }

    checkLike("options: intensity-dir", "test/data/160916_miseq_0966_FC/Data/Intensities", opts->intensity_dir);
    checkEqual("options: output-file", "test/data/out/xxx.sam", opts->output_file);
    checkEqual("options: sample-alias", "testlibrary", opts->sample_alias);
    checkEqual("options: study-name", "teststudy", opts->study_name);
    checkLike("options: run-folder", "test/data/160916_miseq_0966_FC", opts->run_folder);
    checkLike("options: basecalls-dir", "test/data/160916_miseq_0966_FC/Data/Intensities/BaseCalls", opts->basecalls_dir);
    icheckEqual("options: lane", 1, opts->lane);
    icheckEqual("options: generate-secondary-basecalls", 1, opts->generate_secondary_basecalls);
    icheckEqual("options: no-filter", 1, opts->no_filter);
    checkEqual("options: read-group-id", "1", opts->read_group_id);
    checkEqual("options: sequencing-centre", "XY", opts->sequencing_centre);
    checkEqual("options: platform", "Illumina", opts->platform);
    icheckEqual("options: first-tile", 1103, opts->first_tile);
    icheckEqual("options: tile-limit", 5, opts->tile_limit);
    checkEqual("options: barcode-tag", "AB", opts->barcode_tag->entries[0]);
    checkEqual("options: quality-tag", "CD", opts->quality_tag->entries[0]);
    checkEqual("options: sec-barcode-tag", "WX", opts->barcode_tag->entries[1]);
    checkEqual("options: sec-quality-tag", "YZ", opts->quality_tag->entries[1]);
    icheckEqual("options: first-cycle", 3, opts->first_cycle->end);
    icheckEqual("options: first-cycle[0]", 7, opts->first_cycle->entries[0]);
    icheckEqual("options: first-cycle[1]", 17, opts->first_cycle->entries[1]);
    icheckEqual("options: first-cycle[2]", 70, opts->first_cycle->entries[2]);
    icheckEqual("options: final-cycle", 3, opts->final_cycle->end);
    icheckEqual("options: final-index-cycle", 1, opts->final_index_cycle->end);
    icheckEqual("options: final-cycle[0]", 16, opts->final_cycle->entries[0]);
    icheckEqual("options: index-separator", 1, opts->separator);
    free_args(argv_1);
    i2b_free_opts(opts);
}

void checkFiles(char *name, char *outputfile, char *fname)
{
    char command[1024];

    sprintf(command,"samtools view -H %s | grep @RG > %s.got.txt", outputfile, outputfile);
    if (system(command)) { fprintf(stderr,"samtools failed\n"); failure++; }
    sprintf(command, "samtools view -H %s | grep @RG > %s.expected.txt", fname, outputfile);
    if (system(command)) { fprintf(stderr,"samtools failed\n"); failure++; }
    sprintf(command,"diff %s.got.txt %s.expected.txt", outputfile, outputfile);
    int result = system(command);
    if (result) {
        fprintf(stderr, "%s: test 1 failed\n", name);
        failure++;
    } else {
        success++;
    }

    sprintf(command,"samtools view %s | head | perl -n -e 'chomp; @x=split /\t/;@y=sort @x; print join \",\",@y; print \"\n\";' > %s.got.txt",outputfile,outputfile);
    if (system(command)) { fprintf(stderr,"samtools failed\n"); failure++; }
    sprintf(command,"samtools view %s | head | perl -n -e 'chomp; @x=split /\t/;@y=sort @x; print join \",\",@y; print \"\n\";' > %s.expected.txt", fname,outputfile);
    if (system(command)) { fprintf(stderr,"samtools failed\n"); failure++; }
    sprintf(command,"diff %s.got.txt %s.expected.txt", outputfile, outputfile);
    result = system(command);
    if (result) {
        fprintf(stderr, "%s: test 2 failed\n", name);
        failure++;
    } else {
        success++;
    }

    sprintf(command,"samtools view %s | tail | perl -n -e 'chomp; @x=split /\t/;@y=sort @x; print join \",\",@y; print \"\n\";' > %s.got.txt", outputfile,outputfile);
    if (system(command)) { fprintf(stderr,"samtools failed\n"); failure++; }
    sprintf(command,"samtools view %s | tail | perl -n -e 'chomp; @x=split /\t/;@y=sort @x; print join \",\",@y; print \"\n\";' > %s.expected.txt", fname,outputfile);
    if (system(command)) { fprintf(stderr,"samtools failed\n"); failure++; }
    sprintf(command,"diff %s.got.txt %s.expected.txt", outputfile, outputfile);
    result = system(command);
    if (result) {
        fprintf(stderr, "%s: test 3 failed\n", name);
        failure++;
    } else {
        success++;
    }
}

int main(int argc, char**argv)
{
    char template[] = "/tmp/bambi.XXXXXX";
    char *TMPDIR = mkdtemp(template);
    int getopt_char;
    while ((getopt_char = getopt(argc, argv, "v")) != -1) {
        switch (getopt_char) {
            case 'v': ++verbose;
                      break;
            default: printf("usage: test_parse_args [-v]\n\n"
                            " -v verbose output\n"
                           );
                     break;
        }
    }

    // Cleanup getopt
    optind = 1;

    if (TMPDIR == NULL) {
        fprintf(stderr,"Can't open temporary directory\n");
        exit(1);
    } else {
        if (verbose) fprintf(stderr,"Created temporary directory: %s\n", TMPDIR);
    }
    char *outputfile = calloc(1,strlen(TMPDIR)+64);

    int argc_1;
    char** argv_1;

    // check if we have samtools
    if (system("which samtools") != 0) {
        fprintf(stderr,"samtools not found. Tests cannot be run\n");
        return EXIT_FAILURE;
    }

    //
    // test that we can read the command line paramaters
    //
    test_paramaters();


    //
    // simple test
    //

    if (verbose) fprintf(stderr,"\n===> Simple test\n");
    sprintf(outputfile,"%s/i2b_1.bam",TMPDIR);
    setup_simple_test(&argc_1, &argv_1, outputfile, verbose);
    main_i2b(argc_1-1, argv_1+1);
    checkFiles("Simple test", outputfile, MKNAME(DATA_DIR,"/out/test1.bam"));
    free_args(argv_1);

    //
    // Test with non-standard read group ID
    //

    if (verbose) fprintf(stderr,"\n===> Read Group ID test\n");
    sprintf(outputfile,"%s/i2b_2.bam",TMPDIR);
    setup_readgroup_test(&argc_1, &argv_1, outputfile, verbose);
    main_i2b(argc_1-1,argv_1+1);
    checkFiles("Read Group ID test", outputfile, MKNAME(DATA_DIR,"/out/test2.bam"));
    free_args(argv_1);

    //
    // cycle range test
    //
    if (verbose) fprintf(stderr,"\n===> Cycle Range test\n");
    sprintf(outputfile,"%s/i2b_4.bam",TMPDIR);
    setup_cyclerange_test(&argc_1, &argv_1, outputfile, verbose);
    main_i2b(argc_1-1,argv_1+1);
    checkFiles("Cycle Range test", outputfile, MKNAME(DATA_DIR,"/out/test4.bam"));
    free_args(argv_1);

    //
    // bc-read test
    //
    if (verbose) fprintf(stderr,"\n===> bc-read test\n");
    sprintf(outputfile,"%s/i2b_5.bam",TMPDIR);
    setup_bcread_test(&argc_1, &argv_1, outputfile, verbose);
    main_i2b(argc_1-1,argv_1+1);
    checkFiles("BC_READ test", outputfile, MKNAME(DATA_DIR,"/out/test5.bam"));
    free_args(argv_1);

    //
    // dual index run
    //
    if (verbose) fprintf(stderr,"\n===> Dual Index test\n");
    sprintf(outputfile,"%s/i2b_6.bam",TMPDIR);
    setup_dualindex_test(&argc_1, &argv_1, outputfile, verbose);
    main_i2b(argc_1-1,argv_1+1);
    checkFiles("Dual Index test", outputfile, MKNAME(DATA_DIR,"/out/test6.bam"));
    free_args(argv_1);

    //
    // multiple barcode tags run
    //
    if (verbose) fprintf(stderr,"\n===> Multiple Tags test\n");
    sprintf(outputfile,"%s/i2b_7.bam",TMPDIR);
    setup_tags_test(&argc_1, &argv_1, outputfile, verbose);
    main_i2b(argc_1-1,argv_1+1);
    checkFiles("Multiple barcode tags test", outputfile, MKNAME(DATA_DIR,"/out/test7.bam"));
    free_args(argv_1);

    //
    // separator test
    //
    if (verbose) fprintf(stderr,"\n===> Separator test\n");
    sprintf(outputfile,"%s/i2b_8.bam",TMPDIR);
    separator_test(&argc_1, &argv_1, outputfile, verbose);
    main_i2b(argc_1-1,argv_1+1);
    checkFiles("separator test", outputfile, MKNAME(DATA_DIR,"/out/test8.bam"));
    free_args(argv_1);

    //
    // no separator test
    //
    if (verbose) fprintf(stderr,"\n===> no Separator test\n");
    sprintf(outputfile,"%s/i2b_9.bam",TMPDIR);
    no_separator_test(&argc_1, &argv_1, outputfile, verbose);
    main_i2b(argc_1-1,argv_1+1);
    checkFiles("no separator test", outputfile, MKNAME(DATA_DIR,"/out/test9.bam"));
    free_args(argv_1);

    //
    // novaseq test
    //
    if (verbose) fprintf(stderr,"\n===> NovaSeq test\n");
    sprintf(outputfile,"%s/novaseq_1.sam",TMPDIR);
    novaseq_test(&argc_1, &argv_1, outputfile, verbose);
    main_i2b(argc_1-1,argv_1+1);
    checkFiles("NovaSeq test", outputfile, MKNAME(DATA_DIR,"/out/novaseq_1.sam"));
    free_args(argv_1);

    free(outputfile);

    printf("i2b tests: %s\n", failure ? "FAILED" : "Passed");
    return failure ? EXIT_FAILURE : EXIT_SUCCESS;
}
