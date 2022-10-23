/*
 * Copyright (C) 2015 Niek Linnenbank
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

#include <Types.h>
#include <Macros.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <ProcessClient.h>
#include "Renice.h"

Renice::Renice(int argc, char **argv)
    : POSIXApplication(argc, argv)
{
    parser().setDescription("Set priority level of a process");
    parser().registerPositional("Prio Level", "Priority level to set");
    parser().registerPositional("Process ID", "ID of the process to modify");
}

Renice::Result Renice::exec()
{
    int procID = 0;
    int prioLevel = 0;

    // Convert procID to int, check that it is a number
    if ((procID = atoi(arguments().get("Process ID"))) < 0)
    {
        ERROR("invalid process ID `" << arguments().get("Process ID") << "'");
        return InvalidArgument;
    }
    // Convert prioLevel to int, check that it is a number
    if ((prioLevel = atoi(arguments().get("Prio Level"))) <= 0)
    {
        ERROR("invalid priority level`" << arguments().get("Prio Level") << "'");
        return InvalidArgument;
    }
    //Check if prio level is between 1 and 5
    if(prioLevel <= 0 || prioLevel > 5)
    {
        ERROR("invalid priority level`" << arguments().get("Prio Level") << "'");
        return InvalidArgument;
    }

    const ProcessClient process;
    ProcessID realProcID = procID;

    process.setPriority(realProcID, prioLevel); //Set the priority of the process, currently broken
    //ProcessCtl(realProcID, SetPriority, 0);     //Attempting to call processCTL directly just to see if it works, DO NOT LEAVE THIS IN

    
    return Success;
}
