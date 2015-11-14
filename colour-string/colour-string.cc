#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string.h>
#include <unistd.h>
#include <pcrecpp.h>

/**
 * We draw lines of colours.
 *
 * These lines are of the form:
 *
 *   $[RED]This is red$[YELLOW]This is yellow.
 *
 * We parse lines like this into arrays of structures,
 * the structure contains the colour-code and the string to
 * draw.
 */
typedef struct _COLOUR_STRING
{
    /**
     * The colour to use for this segment.
     */
    std::string *colour;

    /**
     * The string itself.
     */
    std::string *string;

} COLOUR_STRING;


/**
 * Parse a string into an array of "string + colour" pairs,
 * which will be useful for drawing strings.
 */
std::vector<COLOUR_STRING *> parse_coloured_string(std::string input)
{
    std::vector<COLOUR_STRING *> results;

    /*
     * I know this is horrid.
     *
     * NOTE: We're tryign to be greedy but searching from the
     * back of the string forward.  This is definitely the simpler
     * of the approaches I trialled.
     */
    pcrecpp::RE re("^(.*)\\$\\[([a-zA-Z]+)\\](.*)$");

    std::string prefix;
    std::string col;
    std::string txt;

    while (re.FullMatch(input, &prefix, &col, &txt))
    {

        /*
         * Allocate a structure to hold this match.
         */
        COLOUR_STRING *tmp = (COLOUR_STRING *)malloc(sizeof(COLOUR_STRING));

        /*
        * Save our match away.
        */
        tmp->colour = new std::string(col);
        tmp->string = new std::string(txt);
        results.push_back(tmp);

        input = prefix;
    }

    /*
     * If input is non-empty then we have leading match.  Handle that
     * as a special case.
     */
    if (! input.empty())
    {
        /*
         * Allocate a structure to hold this match.
         */
        COLOUR_STRING *tmp = (COLOUR_STRING *)malloc(sizeof(COLOUR_STRING));
        tmp->colour = new std::string("default");
        tmp->string = new std::string(input);
        results.push_back(tmp);
    }

    /*
     * Remember we searched backwards?  Reverse so all makes sense.
     */
    std::reverse(results.begin(), results.end());
    return (results);
}


/**
 * Test our code against the first argument.
 */
int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cerr << "Usage: " << argv[0] << "'string to parse'" << std::endl;
        return -1;
    }

    /*
     * Call the magic.
     */
    std::vector<COLOUR_STRING*> out = parse_coloured_string(argv[1]);

    /*
     * Show the results.
     */
    for (auto it = out.begin(); it != out.end() ; ++it)
    {
        COLOUR_STRING *i = (*it);
        std::cout << *i->colour << " string: '" << *i->string << "'\n";
    }

    return 0;
}
