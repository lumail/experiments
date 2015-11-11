#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string.h>
#include <unistd.h>

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
    std::regex base_regex("^(.*)\\$\\[([a-zA-Z]+)\\](.*)$");
    std::smatch base_match;

    while (std::regex_match(input, base_match, base_regex))
    {

        /*
         * Allocate a structure to hold this match.
         */
        COLOUR_STRING *tmp = (COLOUR_STRING *)malloc(sizeof(COLOUR_STRING));

        std::ssub_match prefix_match = base_match[1];
        std::string prefix = prefix_match.str();

        std::ssub_match colour_match = base_match[2];
        std::string colour = colour_match.str();

        std::ssub_match str_match = base_match[3];
        std::string str = str_match.str();

        /*
        * Save our match away.
        */
        tmp->colour = new std::string(colour);
        tmp->string = new std::string(str);
        results.push_back(tmp);

        input = prefix;
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
