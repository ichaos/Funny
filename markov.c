#include <stdio.h>
#include <string.h>
#include <stdlib.h>

enum {
	NPREF = 2,		/* number of prefix words */
	MULTIPLIER = 31, /* the multiplier for hash computing */
	NHASH = 4093,	/* size of state hash table array */
	MAXGEN = 10000, /* maximum words generated */
};

typedef struct State State;
typedef struct Suffix Suffix;
struct State {
	char *pref[NPREF];		/* prefix words */
	Suffix *suf;			/* list of suffix words */
	State *next;			/* next in hash table */
};

struct Suffix {
	char *word;				/* suffix */
	Suffix *next;			/* next in list of suffixes */
};

State *statetab[NHASH];		/* hash table of states */

/* hash: compute hash value for array of NPREF strings */
unsigned int hash(char *s[NPREF]) {
	unsigned int h = 0;
	unsigned char *p;
	int i;

	for (i = 0; i < NPREF; i++) {
		for (p = (unsigned char *)s[i]; *p != '\0'; p++) {
			h = MULTIPLIER * h + (*p);
		}
	}

	return h % NHASH;
}

/* lookup: search for prefix, create if requested */
/* return pointer if present or created; NULL if not */
/* creation doesn't strdup, so string must not change later */
State * lookup(char *prefix[NPREF], int create) {
	int i, h;
	h = hash(prefix);
	State *s = statetab[h];

	for (; s != NULL; s = s->next) {
		for (i = 0; i < NPREF; i++) {
			if (strcmp(prefix[i], s->pref[i]))
				break;
		}
		if (i == NPREF)
			return s;
	}

	if (create) {
		s = (State *)malloc(sizeof(State));
		for (i = 0; i < NPREF; i++)
			s->pref[i] = prefix[i];
		s->suf = NULL;
		s->next = statetab[h];
		statetab[h] = s;
	}

	return s;
}

/* addsuffix: add to state. suffix must not change later */
void addsuffix(State *sp, char *suffix) {
	Suffix *suf;
	suf = (Suffix *)malloc(sizeof(Suffix));
	suf->word = suffix;
	suf->next = sp->suf;
	sp->suf = suf;
}

/* add: add word to suffix list, update prefix */
void add(char *prefix[NPREF], char *suffix) {
	State *sp;

	sp = lookup(prefix, 1);
	addsuffix(sp, suffix);
	memmove(prefix, prefix + 1, (NPREF - 1) * sizeof(prefix[0]));
	prefix[NPREF - 1] = suffix;
}

/* build: read input, build prefix table */
void build(char *prefix[NPREF], FILE *f) {
	char buf[100], fmt[10];

	/* create a format string; %s could overflow buf */
	sprintf(fmt, "%%%ds", sizeof(buf) - 1);
	while (fscanf(f, fmt, buf) != EOF) {
		add(prefix, strdup(buf));
	}
}

char NONWORD[] = "\n";

/* generate: produce output, one word per line */
void generate(int nwords) {
	State *sp;
	Suffix *suf;
	char *prefix[NPREF], *w;
	int i, nmatch;

	for (i = 0; i < NPREF; i++) {
		prefix[i] = NONWORD;
	}

	for (i = 0; i < nwords; i++) {
		sp = lookup(prefix, 0);
		nmatch = 0;
		for (suf = sp->suf; suf; suf = suf->next) {
			if (rand() % ++nmatch == 0)
				w = suf->word;
		}

		if (strcmp(w, NONWORD) == 0)
			break;
		printf("%s ", w);
		memmove(prefix, prefix + 1, (NPREF - 1) * sizeof(prefix[0]));
		prefix[NPREF - 1] = w;
	}
}

/* markov main: markov-chain random text generation */
int main(void)
{
	int i, nwords = MAXGEN;
	char *prefix[NPREF];

	for (i = 0; i < NPREF; i++) {
		prefix[i] = NONWORD;
	}
	build(prefix, stdin);
	add(prefix, NONWORD);
	generate(nwords);
	return 0;
}
