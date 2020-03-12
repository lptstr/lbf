#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "instructions.h"
#include "lbf.h"
#include "parser.h"
#include "util.h"

void
parse(struct Options *opts, char *program_data, struct Instruction *program)
{
	usize len  = strlen(program_data);
	if (opts->debug) debug("length of program data = %d", len);
	usize line = 0;
	usize column = 0;

	struct Instruction *last = program;

	for (usize i = 0; i < len; ++i) {
		if (opts->verbose)
			fprintf(stderr, "\rparsing command %d / %d... ", i, len);
		program_data[i] == '\n' ? ++line : ++column;

		usize command;

		switch (program_data[i]) {
		case '*':
		case '+':
		case '-':
		case '[':
		case ']':
		case '^':
		case '<':
		case '>':
		case ',':
		case '.':
		case '&':
		case '#':
		case '{':
		case '}':
		case '@':
			command = program_data[i];
			break;
		default:
			continue;
			break;
		}

		struct Instruction *inst = malloc(sizeof(struct Instruction));
		inst->command = command;
		inst->line    = line;
		inst->column  = column,
		inst->repeat  = 1;
		inst->prev    = last;
		last->next    = inst;

		last = inst;
	}

	if (opts->verbose) fprintf(stderr, "done \n");
}
