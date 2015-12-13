
/*******************************   stem.c   ***********************************

   Purpose:    Implementation of the Porter stemming algorithm documented 
               in: Porter, M.F., "An Algorithm For Suffix Stripping," 
               Program 14 (3), July 1980, pp. 130-137.

   Provenance: Written by B. Frakes and C. Cox, 1986.
               Changed by C. Fox, 1990.
                  - made measure function a DFA
                  - restructured structs
                  - renamed functions and variables
                  - restricted function and variable scopes
               Changed by C. Fox, July, 1991.
                  - added ANSI C declarations 
                  - branch tested to 90% coverage

   Notes:      This code will make little sense without the the Porter
               article.  The stemming function converts its input to
               lower case.
**/

/************************   Standard Include Files   *************************/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*****************************************************************************/
/*****************   Private Defines and Data Structures   *******************/

#define FALSE                         0
#define TRUE                          1
#define EOS                         '\0'

#define IsVowel(c)        ('a'==(c)||'e'==(c)||'i'==(c)||'o'==(c)||'u'==(c)||'á'==(c)||'é'==(c)||'í'==(c)||'ó'==(c)||'ú'==(c))

typedef struct {
           int id;                 /* returned if rule fired */
           char *old_end;          /* suffix replaced */
           char *new_end;          /* suffix replacement */
           int old_offset;         /* from end of word to start of suffix */
           int new_offset;         /* from beginning to end of new suffix */
           int min_root_size;      /* min root word size for replacement */
           int (*condition)();     /* the replacement test function */
           } RuleList;

static char LAMBDA[1] = "";        /* the constant empty string */
static char *end;                  /* pointer to the end of the word */

/*****************************************************************************/
/********************   Private Function Declarations   **********************/

#ifdef __STDC__

static int WordSize( char *word );
static int ContainsVowel( char *word );
static int EndsWithCVC( char *word );
static int AddAnE( char *word );
static int RemoveAnE( char *word );
static int ReplaceEnd( char *word, RuleList rule );
static int EndsWithVowels( char *word );

#else

static int WordSize( /* word */ );
static int ContainsVowel( /* word */ );
static int EndsWithCVC( /* word */ );
static int AddAnE( /* word */ );
static int RemoveAnE( /* word */ );
static int ReplaceEnd( /* word, rule */ );

#endif

/******************************************************************************/
/*****************   Initialized Private Data Structures   ********************/

static RuleList step00_rules[] =
 {  001, "es",      LAMBDA,     1,  -1,   0,    EndsWithDLR,
    002, "mente",   LAMBDA,     4,  -1,   0,    NULL,
    000, NULL,      NULL,       0,   0,   0,    NULL, };

static RuleList step01_rules[] =
 {  004, "al",      "a",        1,   0,   0,    EndsWithVowels,
    005, "al",      LAMBDA,     1,  -1,   0,    NULL,
    000, NULL,      NULL,       0,   0,   0,    NULL, };

static RuleList step1a_rules[] =
 {  101, "ces",     "z",        2,  -1,  -1,    NULL,
    102, "r",       LAMBDA,     0,  -1,   0,    NULL,
    103, "nos",     LAMBDA,     2,  -1,   1,    EndsWithOR,
    104, "s",       LAMBDA,     0,  -1,   0,    NULL,
    105, "cion",    "r",        3,   0,   0,    NULL,
    106, "ción",    "r",        3,   0,   0,    NULL,
    107, "n",       LAMBDA,     0,  -1,   0,    NULL,
    000, NULL,      NULL,       0,   0,   0,    NULL, };

static RuleList step1b_rules[] =
 {  110, "ente",    LAMBDA,     3,  -1,   0,    NULL,
    111, "encia",   LAMBDA,     4,  -1,   0,    NULL,
    112, "dr¡a",    LAMBDA,     3,  -1,   0,    NULL,
    113, "mo",      LAMBDA,     1,  -1,   0,    NULL,
    114, "ro",      LAMBDA,     1,  -1,   0,    NULL,
    115, "se",      LAMBDA,     1,  -1,   0,    NULL,
    116, "la",      LAMBDA,     1,  -1,   0,    EndsWithOR,
    117, "le",      LAMBDA,     1,  -1,   0,    EndsWithOR,
    118, "lo",      LAMBDA,     1,  -1,   0,    EndsWithOR,
    119, "me",      LAMBDA,     1,  -1,   0,    EndsWithOR,
    120, "do",      LAMBDA,     1,  -1,  -1,    NULL,
    121, "da",      LAMBDA,     1,  -1,  -1,    EndsWithVowels,
    000, NULL,      NULL,       0,   0,   0,    NULL, }; 

static RuleList step1b1_rules[] =
 {  125, "n",       LAMBDA,     0,  -1,   0,    NULL,
    000, NULL,      NULL,       0,   0,   0,    NULL,};

static RuleList step1b2_rules[] =
 {  130, "re",      "r",        1,   0,   0,    EndsWithVowels,
    000, NULL,      NULL,       0,   0,   0,    NULL, };

static RuleList step2_rules[] =
 {  220, " ",       LAMBDA,     0,  -1,   0,    NULL,
    221, "iza",     LAMBDA,     2,  -1,   0,    NULL,
    222, "iz¢",     LAMBDA,     2,  -1,   0,    NULL,
    223, "izar",    LAMBDA,     3,  -1,   0,    NULL,
    224, "¡a",      LAMBDA,     1,  -1,   0,    NULL,
    225, "imiento", "e",        6,   0,   0,    NULL,
    226, "miento",  LAMBDA,     5,  -1,   0,    NULL,
    227, "tivo",    LAMBDA,     3,  -1,   0,    NULL,
    228, "tiva",    LAMBDA,     3,  -1,   0,    NULL,
    228, "tiv",     LAMBDA,     2, - 1,   0,    NULL,
    229, "ble",     LAMBDA,     2,  -1,   0,    NULL,
    230, "bl",      LAMBDA,     1,  -1,   0,    NULL,
    231, "dad",     LAMBDA,     2,  -1,   0,    EndsWithVowels,
    232, "ize",     LAMBDA,     2,  -1,   0,    NULL,
    233, "iz",      LAMBDA,     1,  -1,   0,    NULL,
    000, NULL, NULL, 0, 0, 0, NULL, };

static RuleList step8_rules[] =
 {  800, "r",       LAMBDA,     0,  -1,   1,    NULL,
    000, NULL,      NULL,       0,   0,   0,    NULL,};

static RuleList step9_rules[] =
 {  990, "a",       LAMBDA,     0,  -1,  -1,    NULL,
    991, "á",       LAMBDA,     0,  -1,  -1,    NULL,
    992, "e",       LAMBDA,     0,  -1,  -1,    NULL,
    993, "é",       LAMBDA,     0,  -1,  -1,    NULL,
    994, "i",       LAMBDA,     0,  -1,  -1,    NULL,
    995, "í",       LAMBDA,     0,  -1,  -1,    NULL,
    996, "o",       LAMBDA,     0,  -1,  -1,    NULL,
    997, "ó",       LAMBDA,     0,  -1,  -1,    NULL,
    998, "u",       LAMBDA,     0,  -1,  -1,    NULL,
    999, "ú",       LAMBDA,     0,  -1,  -1,    NULL,
    000, NULL,      NULL,       0,   0,   0,    NULL, };

static RuleList step99_rules[] =
 {  990, "a",       LAMBDA,     0,  -1,  -1,    NULL,
    991, "á",       LAMBDA,     0,  -1,  -1,    NULL,
    992, "e",       LAMBDA,     0,  -1,  -1,    NULL,
    993, "é",       LAMBDA,     0,  -1,  -1,    NULL,
    994, "i",       LAMBDA,     0,  -1,  -1,    NULL,
    995, "í",       LAMBDA,     0,  -1,  -1,    NULL,
    996, "o",       LAMBDA,     0,  -1,  -1,    NULL,
    997, "ó",       LAMBDA,     0,  -1,  -1,    NULL,
    998, "u",       LAMBDA,     0,  -1,  -1,    NULL,
    999, "ú",       LAMBDA,     0,  -1,  -1,    NULL,
    000, NULL,      NULL,       0,   0,   0,    NULL, };

/*****************************************************************************/
/********************   Private Function Declarations   **********************/

/*FN***************************************************************************

       WordSize( word )

   Returns: int -- a weird count of word size in adjusted syllables

   Purpose: Count syllables in a special way:  count the number 
            vowel-consonant pairs in a word, disregarding initial 
            consonants and final vowels.  The letter "y" counts as a
            consonant at the beginning of a word and when it has a vowel
            in front of it; otherwise (when it follows a consonant) it
            is treated as a vowel.  For example, the WordSize of "cat" 
            is 1, of "any" is 1, of "amount" is 2, of "anything" is 3.

   Plan:    Run a DFA to compute the word size

   Notes:   The easiest and fastest way to compute this funny measure is
            with a finite state machine.  The initial state 0 checks
            the first letter.  If it is a vowel, then the machine changes
            to state 1, which is the "last letter was a vowel" state.
            If the first letter is a consonant or y, then it changes
            to state 2, the "last letter was a consonant state".  In
            state 1, a y is treated as a consonant (since it follows
            a vowel), but in state 2, y is treated as a vowel (since
            it follows a consonant.  The result counter is incremented
            on the transition from state 1 to state 2, since this
            transition only occurs after a vowel-consonant pair, which
            is what we are counting.
**/

static int
WordSize( word )
   char *word;   /* in: word having its WordSize taken */
   {
   register int result;   /* WordSize of the word */
   register int state;    /* current state in machine */

   result = 0;
   state = 0;

                 /* Run a DFA to compute the word size */
   while ( EOS != *word )
      {
      switch ( state )
         {
         case 0: state = (IsVowel(*word)) ? 1 : 2;
                 break;
         case 1: state = (IsVowel(*word)) ? 1 : 2;
                 if ( 2 == state ) result++;
                 break;
         case 2: state = (IsVowel(*word) || ('y' == *word)) ? 1 : 2;
                 break;
         }
      word++;
      }

   return( result );

   } /* WordSize */

/*FN**************************************************************************

       ContainsVowel( word )

   Returns: int -- TRUE (1) if the word parameter contains a vowel,
            FALSE (0) otherwise.

   Purpose: Some of the rewrite rules apply only to a root containing
            a vowel, where a vowel is one of "aeiou" or y with a
            consonant in front of it.

   Plan:    Obviously, under the definition of a vowel, a word contains
            a vowel iff either its first letter is one of "aeiou", or
            any of its other letters are "aeiouy".  The plan is to
            test this condition.

   Notes:   None
**/

static int
ContainsVowel( word )
   char *word;   /* in: buffer with word checked */
   {

   if ( EOS == *word )
      return( FALSE );
   else
      return( IsVowel(*word) || (NULL != strpbrk(word+1,"aeiouy")) );


   } /* ContainsVowel */

   static int
EndsWithVowels( word )
   char *word;   /* in: buffer with word checked */
   {

   if ( EOS == *word )
      return( FALSE );
   else{
       int tam;
       tam = strlen(word);
      return( IsVowel(word[tam-1]));
        }   

   } /* endsWithVowels */
   
/*FN**************************************************************************

       EndsWithCVC( word )

   Returns: int -- TRUE (1) if the current word ends with a
            consonant-vowel-consonant combination, and the second
            consonant is not w, x, or y, FALSE (0) otherwise.

   Purpose: Some of the rewrite rules apply only to a root with
            this characteristic.

   Plan:    Look at the last three characters.

   Notes:   None
**/

static int
EndsWithCVC( word )
   char *word;   /* in: buffer with the word checked */
   {
   int length;         /* for finding the last three characters */

   if ( (length = strlen(word)) < 2 )
      return( FALSE );
   else
      {
      end = word + length - 1;
      return(    (NULL == strchr("aeiouwxy",*end--))      /* consonant */
              && (NULL != strchr("aeiouy",  *end--))        /* vowel */
              && (NULL == strchr("aeiou",   *end  )) );   /* consonant */
      }

   } /* EndsWithCVC */

/*FN**************************************************************************

       AddAnE( word )

   Returns: int -- TRUE (1) if the current word meets special conditions
            for adding an e.

   Purpose: Rule 122 applies only to a root with this characteristic.

   Plan:    Check for size of 1 and a consonant-vowel-consonant ending.

   Notes:   None
**/

static int
AddAnE( word )
   char *word;
   {

   return( (1 == WordSize(word)) && EndsWithCVC(word) );

   } /* AddAnE */

/*FN**************************************************************************

       RemoveAnE( word )

   Returns: int -- TRUE (1) if the current word meets special conditions
            for removing an e.

   Purpose: Rule 502 applies only to a root with this characteristic.

   Plan:    Check for size of 1 and no consonant-vowel-consonant ending.

   Notes:   None
**/

static int
RemoveAnE( word )
   char *word;
   {

   return( (1 == WordSize(word)) && !EndsWithCVC(word) );

   } /* RemoveAnE */

/*FN**************************************************************************

       ReplaceEnd( word, rule )

   Returns: int -- the id for the rule fired, 0 is none is fired

   Purpose: Apply a set of rules to replace the suffix of a word

   Plan:    Loop through the rule set until a match meeting all conditions
            is found.  If a rule fires, return its id, otherwise return 0.
            Connditions on the length of the root are checked as part of this
            function's processing because this check is so often made.

   Notes:   This is the main routine driving the stemmer.  It goes through
            a set of suffix replacement rules looking for a match on the
            current suffix.  When it finds one, if the root of the word
            is long enough, and it meets whatever other conditions are
            required, then the suffix is replaced, and the function returns.
**/

static int
ReplaceEnd( word, rule )
   char *word;        /* in/out: buffer with the stemmed word */
   RuleList *rule;    /* in: data structure with replacement rules */
   {
   register char *ending;   /* set to start of possible stemmed suffix */
   char tmp_ch;             /* save replaced character when testing */

   while ( 0 != rule->id )
      {
      ending = end - rule->old_offset;
      if ( word <= ending )
         if ( 0 == strcmp(ending,rule->old_end) )
            {
            tmp_ch = *ending;
            *ending = EOS;
            if ( rule->min_root_size < WordSize(word) )
               if ( !rule->condition || (*rule->condition)(word) )
                  {
                  (void)strcat( word, rule->new_end );
                  end = ending + rule->new_offset;
                  break;
                  }
            *ending = tmp_ch;
            }
      rule++;
      }

   return( rule->id );

   } /* ReplaceEnd */

/*****************************************************************************/
/*********************   Public Function Declarations   **********************/

/*FN***************************************************************************

       Stem( word )

   Returns: int -- FALSE (0) if the word contains non-alphabetic characters
            and hence is not stemmed, TRUE (1) otherwise

   Purpose: Stem a word

   Plan:    Part 1: Check to ensure the word is all alphabetic
            Part 2: Run through the Porter algorithm
            Part 3: Return an indication of successful stemming

   Notes:   This function implements the Porter stemming algorithm, with
            a few additions here and there.  See:

               Porter, M.F., "An Algorithm For Suffix Stripping,"
               Program 14 (3), July 1980, pp. 130-137.

            Porter's algorithm is an ad hoc set of rewrite rules with
            various conditions on rule firing.  The terminology of
            "step 1a" and so on, is taken directly from Porter's
            article, which unfortunately gives almost no justification
            for the various steps.  Thus this function more or less
            faithfully refects the opaque presentation in the article.
            Changes from the article amount to a few additions to the
            rewrite rules;  these are marked in the RuleList data
            structures with comments.
**/

int
Stem( word )
   char *word;  /* in/out: the word stemmed */
   {
   int rule;    /* which rule is fired in replacing an end */

            /* Part 1: Check to ensure the word is all alphabetic */
   for ( end = word; *end != EOS; end++ )
      if ( !isalpha(*end) ) return( FALSE );
      else *end = tolower( *end );
   end--;

                /*  Part 2: Run through the Porter algorithm */
   (void)ReplaceEnd( word, step1a_rules );
   rule = ReplaceEnd( word, step1b_rules );
   if ( (106 == rule) || (107 == rule) )
      (void)ReplaceEnd( word, step1b1_rules );
   (void)ReplaceEnd( word, step1c_rules );

   (void)ReplaceEnd( word, step2_rules );

   (void)ReplaceEnd( word, step3_rules );

   (void)ReplaceEnd( word, step4_rules );

   (void)ReplaceEnd( word, step5a_rules );
   (void)ReplaceEnd( word, step5b_rules );

           /* Part 3: Return an indication of successful stemming */
   return( TRUE );

   } /* Stem */
