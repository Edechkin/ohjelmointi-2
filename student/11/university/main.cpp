/* This program "illustrates" a University information system.
* Name: Eetu Jokinen
* Student number: 273281
* UserID: teekkart ( Necessary due to gitlab folder naming. )
* eetu.jokinen@tuni.fi
* */


#include "utils.hh"
#include "cli.hh"
#include "university.hh"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

const std::string PROMPT = "Uni> ";


int main()
{
    University* university = new University();
    Cli cli(university, PROMPT);
    while ( cli.exec() ){}

    delete university;
    return EXIT_SUCCESS;
}
