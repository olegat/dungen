//
//  Parser.cpp
//  Dissert
//
//  Created by Olivier Legat on 28/05/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "ProfileParser.h"

#include <Generator/Generator.h>

Array<Object*> ProfileParser::RandomArray;
Array<Digger*>  ProfileParser::DiggerArray;

#define profileParseError(s) {\
    std::cout << filename << ":" << lineNumber << ":: " << (s) << std::endl;\
	file.close();\
    return false;}
#define readOneLine() {\
    getline(file,line); lineNumber++; line=RemoveWhiteChars(line);\
	if (file.eof()) profileParseError( "unexpected end-of-file (missing '}')." );}

bool ProfileParser::ParseProfile(String filename, long seed, Maze* maze)
{
    String line, value;
    int lineNumber = 0;
    int i, n;
    
    std::cout << "ProfileParser:: using profile: " << filename << std::endl;
    
    // Open file:
    Ifstream file;
    file.open ( filename.c_str() );
    if ( file.bad() ) profileParseError( "Failed to open " + filename );
    
    // Parse amount of random number generators:
    {
        readOneLine();
        if ( ! GetValue(line, "RandomCount", &value) ) profileParseError( "RandomCount expected." );
        RandomArray.clear();
        RandomArray = Array<Object*> ( atoi (value.c_str()), NULL);
        readOneLine();
        if ( line != "{" ) profileParseError( "{ expected." );
    }
    
    // Parse the random number generators:
    {
        n = (int)RandomArray.size();
        for (i = 0; i < n; i++)
        {
            readOneLine();
            if ( line == "UniformRandom" )
            {
                readOneLine();
                if ( line != "{" ) profileParseError( "{ expected." );
                readOneLine();
                if ( line == "}" )
                    RandomArray[i] = new UniformRandom ( seed );
                else if (GetValue(line, "Seed", &value))
                {
                    RandomArray[i] = new UniformRandom ( atoi (value.c_str()) );
                    readOneLine();
                    if (line != "}") profileParseError( "} expected." );
                }
                else profileParseError("Seed expected.");
            }
            else if ( line == "RandomTurner" )
            {
                float right = 0.15f, left = 0.15f;
                int randomi = 0, randomf = 0;
                
                readOneLine();
                if ( line != "{" ) profileParseError( "{ expected." );
                while (line != "}")
                {
                    readOneLine();
                    if ( GetValue(line, "RandomI", &value) ) randomi = atoi ( value.c_str() );
                    else if ( GetValue(line, "RandomF", &value) ) randomi = atoi ( value.c_str() );
                    else if ( GetValue(line, "LeftProb", &value) ) left = (float) atof(value.c_str());
                    else if ( GetValue(line, "RightProb",&value) ) right= (float) atof(value.c_str());
                }
                RandomI* randi = dynamic_cast<RandomI*> ( RandomArray[randomi] );
                RandomF* randf = dynamic_cast<RandomF*> ( RandomArray[randomf] );
                if (randi==NULL) profileParseError("Un-acceptable RandomI.");
                if (randf==NULL) profileParseError("Un-acceptable RandomF.");
                
                RandomArray[i] = new RandomTurner (randi, randf, left, right);
            }
        }
        readOneLine();
        if (line != "}") profileParseError( "} expected." );
    }
    
    // Parse the amount of diggers:
    {
        readOneLine();
        if ( ! GetValue(line, "DiggerCount", &value) ) profileParseError( "DiggerCount expected." );
        DiggerArray.clear();
        DiggerArray = Array<Digger*> ( atoi (value.c_str()), NULL);
        readOneLine();
        if ( line != "{" ) profileParseError( "{ expected." );
    }
    
    // Parse the random number generators:
    {
        n = (int)DiggerArray.size();
        for (i = 0; i < n; i++)
        {
            readOneLine();

            if ( line == "DFSDigger" )
            {
                readOneLine();
                if (line != "{") profileParseError("{ expected.");
                int randomi = 0;
                while ( line != "}")
                {
                    readOneLine();
                    if ( GetValue(line, "RandomI", &value) ) randomi = atoi ( value.c_str() );
                }
                if (randomi < 0 || randomi >= RandomArray.size()) 
                    profileParseError("RandomI index out of range.");
                
                RandomI* randi = dynamic_cast<RandomI*> ( RandomArray[ randomi ] );
                
                if (randi == NULL) profileParseError("Un-exceptable RandomI.")
                    DiggerArray[i] = new DFSDigger(maze, randi);
            }
            
            else if ( line == "PrimDigger" )
            {
                readOneLine();
                if (line != "{") profileParseError("{ expected.");
                int randomi = 0;
                while ( line != "}")
                {
                    readOneLine();
                    if ( GetValue(line, "RandomI", &value) ) randomi = atoi ( value.c_str() );
                }
                if (randomi < 0 || randomi >= RandomArray.size()) 
                    profileParseError("RandomI index out of range.");
                
                RandomI* randi = dynamic_cast<RandomI*> ( RandomArray[ randomi ] );
                
                if (randi == NULL) profileParseError("Un-exceptable RandomI.")
                    DiggerArray[i] = new PrimDigger(maze, randi);
            }
            
            else if ( line == "KruskalDigger" )
            {
                readOneLine();
                if (line != "{") profileParseError("{ expected.");
                int randomi = 0;
                while ( line != "}")
                {
                    readOneLine();
                    if ( GetValue(line, "RandomI", &value) ) randomi = atoi ( value.c_str() );
                }
                if (randomi < 0 || randomi >= RandomArray.size()) 
                    profileParseError("RandomI index out of range.");
                
                RandomI* randi = dynamic_cast<RandomI*> ( RandomArray[ randomi ] );
                
                if (randi == NULL) profileParseError("Un-exceptable RandomI.")
                    DiggerArray[i] = new KruskalDigger(maze, randi);
            }
            
            else if ( line == "BinaryTreeDigger" )
            {
                readOneLine();
                if (line != "{") profileParseError("{ expected.");
                int randomi = 0;
                while ( line != "}")
                {
                    readOneLine();
                    if ( GetValue(line, "RandomI", &value) ) randomi = atoi ( value.c_str() );
                }
                if (randomi < 0 || randomi >= RandomArray.size()) 
                    profileParseError("RandomI index out of range.");
                
                RandomI* randi = dynamic_cast<RandomI*> ( RandomArray[ randomi ] );
                
                if (randi == NULL) profileParseError("Un-exceptable RandomI.")
                    DiggerArray[i] = new BinaryTreeDigger(maze, randi);
            }
            
			else if ( line == "StartEndDigger" )
            {
                readOneLine();
                if (line != "{") profileParseError("{ expected.");
                while ( line != "}") {readOneLine();}
                DiggerArray[i] = new StartEndDigger(maze);
            }

            else if ( line == "DeadEndDigger" )
            {
                readOneLine();
                if (line != "{") profileParseError("{ expected.");
                int sparseness = 3;
                while ( line != "}")
                {
                    readOneLine();
                    if ( GetValue(line, "Sparseness", &value) ) sparseness = atoi ( value.c_str() );
                }
                if (sparseness <= 0) profileParseError("Sparseness must be greater than 0.");
                DiggerArray[i] = new DeadEndDigger(maze, sparseness);
            }
            
            else if ( line == "RoomDigger" )
            {
                readOneLine();
                if (line != "{") profileParseError("{ expected.");
                RandomElementI roomSize   (1, 3);  int sizei;
                RandomElementI roomPos    (0, 25); int posi;
                RandomElementI roomAmount (3, 6);  int amounti;
                while ( line != "}")
                {
                    readOneLine();
                    if ( GetValue(line, "MinRoomSize", &value) ) roomSize.min = atoi ( value.c_str() );
                    else if ( GetValue(line, "MaxRoomSize", &value) ) roomSize.max = atoi ( value.c_str() );
                    else if ( GetValue(line, "RoomSizeRandomI", &value) ) sizei = atoi ( value.c_str() );
                    
                    else if ( GetValue(line, "MinRoomPos", &value) ) roomPos.min = atoi ( value.c_str() );
                    else if ( GetValue(line, "MaxRoomPos", &value) ) roomPos.max = atoi ( value.c_str() );
                    else if ( GetValue(line, "RoomPosRandomI", &value) ) posi = atoi ( value.c_str() );
                    
                    else if ( GetValue(line, "MinNRooms", &value) ) roomAmount.min = atoi ( value.c_str() );
                    else if ( GetValue(line, "MaxNRooms", &value) ) roomAmount.max = atoi ( value.c_str() );
                    else if ( GetValue(line, "NRoomRandomI", &value) ) amounti = atoi ( value.c_str() );
                }
                if (roomSize.min   <= 0) profileParseError("MinRoomSize must be greater than 0.");
                if (roomAmount.min <= 0) profileParseError("MinRoomAmount must be greater than 0.");
                
                roomSize.generator   = dynamic_cast<RandomI*>( RandomArray[sizei] );
                roomPos.generator    = dynamic_cast<RandomI*>( RandomArray[posi] );
                roomAmount.generator = dynamic_cast<RandomI*>( RandomArray[amounti] );
                
                if ( roomSize.generator   == 0) profileParseError("Un-acceptable RoomSizeRandomI");
                if ( roomPos.generator    == 0) profileParseError("Un-acceptable RoomPosRandomI");
                if ( roomAmount.generator == 0) profileParseError("Un-acceptable NRoomRandomI");
                
                DiggerArray[i] = new RoomDigger(maze, roomSize, roomPos, roomAmount);
            }
            
            else if ( line == "WeighedRoomDigger" )
            {
                readOneLine();
                if (line != "{") profileParseError("{ expected.");
                RoomDiggerWeights weight;
                weight.OnRoom = 100;
                weight.OnCorridor = 3;
                weight.TouchingCorridor = 1;
                
                RandomElementI roomSize   (1, 3);  int sizei;
                RandomElementI roomPos    (0, 25); int posi;
                RandomElementI roomAmount (3, 6);  int amounti;
                while ( line != "}")
                {
                    readOneLine();
                    if ( GetValue(line, "MinRoomSize", &value) ) roomSize.min = atoi ( value.c_str() );
                    else if ( GetValue(line, "MaxRoomSize", &value) ) roomSize.max = atoi ( value.c_str() );
                    else if ( GetValue(line, "RoomSizeRandomI", &value) ) sizei = atoi ( value.c_str() );
                    
                    else if ( GetValue(line, "MinRoomPos", &value) ) roomPos.min = atoi ( value.c_str() );
                    else if ( GetValue(line, "MaxRoomPos", &value) ) roomPos.max = atoi ( value.c_str() );
                    else if ( GetValue(line, "RoomPosRandomI", &value) ) posi = atoi ( value.c_str() );
                    
                    else if ( GetValue(line, "MinNRooms", &value) ) roomAmount.min = atoi ( value.c_str() );
                    else if ( GetValue(line, "MaxNRooms", &value) ) roomAmount.max = atoi ( value.c_str() );
                    else if ( GetValue(line, "NRoomRandomI", &value) ) amounti = atoi ( value.c_str() );
                    
                    else if ( GetValue(line, "PenaltyOnRoom", &value) ) weight.OnRoom = atoi ( value.c_str() );
                    else if ( GetValue(line, "PenaltyOnCorridor", &value) ) weight.OnCorridor = atoi ( value.c_str() );
                    else if ( GetValue(line, "PenaltyTouchingCorridor", &value) ) weight.TouchingCorridor = atoi ( value.c_str() );
                }
                if (roomSize.min   <= 0) profileParseError("MinRoomSize must be greater than 0.");
                if (roomAmount.min <= 0) profileParseError("MinRoomAmount must be greater than 0.");
                
                roomSize.generator   = dynamic_cast<RandomI*>( RandomArray[sizei] );
                roomPos.generator    = dynamic_cast<RandomI*>( RandomArray[posi] );
                roomAmount.generator = dynamic_cast<RandomI*>( RandomArray[amounti] );
                
                if ( roomSize.generator   == 0) profileParseError("Un-acceptable RoomSizeRandomI");
                if ( roomPos.generator    == 0) profileParseError("Un-acceptable RoomPosRandomI");
                if ( roomAmount.generator == 0) profileParseError("Un-acceptable NRoomRandomI");
                
                DiggerArray[i] = new WeighedRoomDigger(maze, weight, roomSize, roomPos, roomAmount);
            }
            
            else if ( line == "LoopDigger" )
            {
                readOneLine();
                if (line != "{") profileParseError("{ expected.");
                int ri = 0, rf = 0;
                float remove = 1;
                while ( line != "}")
                {
                    readOneLine();
                    if ( GetValue(line, "RandomI", &value) ) ri = atoi ( value.c_str() );
                    else if ( GetValue(line, "RandomF", &value) ) rf = atoi ( value.c_str() );
                    else if ( GetValue(line, "RemoveProb", &value) ) remove = (float) atof(value.c_str());
                }

				if (remove < 0 || remove > 1) profileParseError("RemoveProb in LoopDigger must be in [0,1] range.");

                RandomI* Ri = dynamic_cast<RandomI*>( RandomArray[ri] );
                RandomF* Rf = dynamic_cast<RandomF*>( RandomArray[rf] );
                
                DiggerArray[i] = new LoopDigger(maze, Ri, Rf, remove);
            }

			else if ( line == "WallDecoDigger" )
			{
				readOneLine();
                if (line != "{") profileParseError("{ expected.");
				int ri=0, rf=0; float density=0.5f; String decoFilename;
                while ( line != "}")
                {
                    readOneLine();
                    if ( GetValue(line, "RandomI", &value) ) ri = atoi ( value.c_str() );
					else if ( GetValue(line, "RandomF", &value) ) rf = atoi ( value.c_str() );
                    else if ( GetValue(line, "Density", &value) ) density = (float) atof(value.c_str());
                    else if ( GetValue(line, "Filename", &value) ) decoFilename = value;
                }
                
				if (density < 0 || density > 1) profileParseError("Density in WallDecoDigger must be in [0,1] range.");
                
                RandomI* Ri = dynamic_cast<RandomI*>( RandomArray[ri] );
                RandomF* Rf = dynamic_cast<RandomF*>( RandomArray[rf] );
                
				DiggerArray[i] = new WallDecoDigger(maze, Ri, Rf, density, decoFilename);
			}
            
            else if ( line == "DoorDecoDigger" )
			{
				readOneLine();
                if (line != "{") profileParseError("{ expected.");
				int ri=0, rf=0; float density=0.5f; String decoFilename;
                while ( line != "}")
                {
                    readOneLine();
                    if ( GetValue(line, "RandomI", &value) ) ri = atoi ( value.c_str() );
					else if ( GetValue(line, "RandomF", &value) ) rf = atoi ( value.c_str() );
                    else if ( GetValue(line, "Density", &value) ) density = (float) atof(value.c_str());
                    else if ( GetValue(line, "Filename", &value) ) decoFilename = value;
                }
                
				if (density < 0 || density > 1) profileParseError("Density in DoorDecoDigger must be in [0,1] range.");
                
                RandomI* Ri = dynamic_cast<RandomI*>( RandomArray[ri] );
                RandomF* Rf = dynamic_cast<RandomF*>( RandomArray[rf] );
                
				DiggerArray[i] = new DoorDecoDigger(maze, Ri, Rf, density, decoFilename);
			}

			else
			{
				profileParseError("Unknown digger "+line);
			}
        }
    }
    
    file.close();
    return true;
}


String ProfileParser::RemoveWhiteChars(String str)
{
    char * chars = new char[str.length() + 1];
    strcpy (chars, str.c_str());
    int j = 0;
    
    for ( int i=0; i<str.length(); i++ )
    {
        if (str[i] == ' ' || str[i] == '\t') continue;
        else chars[j++] = str[i];
    }
    
    chars[j] = '\0';
    String ret = chars;
    delete [] chars;
    
    return ret;
}


bool ProfileParser::GetValue(String wholeString, String keyWord, String* value)
{
    String prefix = wholeString.substr(0, keyWord.length());
    
    if ( prefix == keyWord )
    {
        prefix.clear();
        int i = (int)wholeString.find_first_of(":");
        i ++;
        
        if ( i < 0 || i >= wholeString.length()) return false;
        
        int len = (int)wholeString.length() - (int)keyWord.length() - 1;
        *value = wholeString.substr(i, len);
        
        return true;
    }
    prefix.clear();
    return false;
}

void ProfileParser::ClearArrays()
{
    size_t i, n;
    
    n = RandomArray.size();
    for(i = 0; i < n; i++) delete RandomArray[i];
    RandomArray.clear();
    
    n = DiggerArray.size();
    for(i = 0; i < n; i++) delete DiggerArray[i];
    DiggerArray.clear();
}
