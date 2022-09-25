/*
 * Copyright (C) 2009 Niek Linnenbank
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
//#include "lib/libposix/sys/wait.h"
#include "../lib/libposix/sys/wait/waitpid.cpp"
#include "../lib/libposix/sys/wait.h"
#include "Wait.h"

Wait::Wait(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Stops a process from executing until the specified process changes state.");
    parser().registerPositional("Process ID", "ID of the process to wait on.");
}

Wait::~Wait()
{

}

Wait::Result Wait::exec()
{

    int procID = 0;

    // Convert input
    if ((procID = atoi(arguments().get("Process ID"))) <= 0)
    {
        ERROR("invalid process ID `" << arguments().get("Process ID") << "'");
        return InvalidArgument;
    }

    //No idea what this status does. Does not need to be initialized. 
    //I couldn't find documentation explaining.
    //Line  36 in waitpid.cpp shows the manipulation of this int. 
    int status;
    int resultPID = waitpid(procID, &status, 0);

    if (resultPID == -1)
    {
        printf("Error: Process ID %d does not exist.\n", procID);
        return NotFound;
    }
    else
    {
        printf("Success: Process ID %d was waited on.\n", procID);
        return Success;
    }
}
