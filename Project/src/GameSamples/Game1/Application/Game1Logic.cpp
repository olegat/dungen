//
//  Game1Logic.cpp
//  
//
//  Created by Olivier Legat on 09/04/12.
//  Copyright (c) 2012 ss42. All rights reserved.
//

#include "Game1App.h"
#include "Game1Logic.h"
#include <Generator/Generator.h>

int Game1Logic::Init() 
{
    EngineApplication* engine = GetEngine();
    
    camera = new Camera();
    camera->SetFreeCam(true);
    camera->yaw = DEG2RAD(90 + 45);
    camera->pitch = DEG2RAD(45);
    camera->y = -3;
    
    scene = engine->GetSceneSpace();
    scene->SetActiveCamera(camera);
    
    if(Game1App::ShowGrid)
    {
        scene->MakeGrid();
        std::cout<< "Scene:: Added grid.." << std::endl;
    }
    
    display = MESH_TEXTURED;
    
    //setUpCube();
    setUpMaze();
    setUpPlayer();
    playing = false;

    return 0;
}

// Used for testing:
void Game1Logic::setUpCube()
{
    Mesh* mesh = new Mesh();
    
    // Declare arrays:
    Array<float> cubeVerts;
    Array<int> cubeInds;
    Array<float> cubeColors;
    
    // Init translation and orientation
    Vector3 pos = Vector3(0, 1, 0);
    Quaternion rot = Quaternion(Vector3(0, 0, PI / 4.0f));
    Vector3 vol = Vector3(1, 2, 3);
    
    // Create data:
    VertexFactory::CreateCuboid(cubeVerts, cubeInds, pos, rot, vol, 1, 1, 1, GL_QUADS);
    VertexFactory::CreateColorArray(cubeColors, (int) cubeVerts.size() / 3, 1.0f, 0.2f, 0.5f);
    
    // Init mesh:
    mesh->SetVertices(&cubeVerts[0], (int)cubeVerts.size());
    mesh->SetIndices(&cubeInds[0], (int)cubeInds.size());
    //mesh->SetColors(&cubeColors[0], (int)cubeColors.size());
    mesh->SetPrimitiveType(GL_QUADS);
    mesh->SetDisplayMode(MESH_TEXTURED);
    
    Texture* diffuse = Texture::CreateFromFile(File("Data/Textures/brick1.png"));
    mesh->GetMaterial()->SetDiffuse(diffuse);
    
    // Init texcoords:
    float texcoords[188];
    for (int i = 0; i < 188; i += 8)
    {
        texcoords[i+0] = 0.0f; texcoords[i+1] = 0.0f;
        texcoords[i+2] = 1.0f; texcoords[i+3] = 0.0f;
        texcoords[i+4] = 1.0f; texcoords[i+5] = 1.0f;
        texcoords[i+6] = 0.0f; texcoords[i+7] = 1.0f;
    }
    mesh->SetTexCoords(&texcoords[0], 188);
    
    // Create the object
    theCube = scene->AddSceneObject("The Cube", mesh);
}

void Game1Logic::setUpMaze()
{
    int i;
    
    GLenum primitiveType = GL_TRIANGLES;
    
    // Init the maze:
    int w = Game1App::MazeWidth, l = Game1App::MazeLength;
    Maze* maze = new Maze(w, l);
    std::cout << "Maze:: Successfully created Maze (" << w << ", " << l << ")." << std::endl;
    
    // Read digger default:
    if (!ProfileParser::ParseProfile(Game1App::ProfileFilename, Game1App::Seed, maze))
        exit(1);
    
    // Now dig dig dig dig dig dig dig in our mine the whole day through.. Heigh-ho!
    Array<Digger*> &diggers = ProfileParser::DiggerArray;
    for ( i = 0; i < diggers.size(); i++)
        diggers[i]->DigFully();
    
    // Make the mesh:
    BasicMeshMaker* maker = new BasicMeshMaker(maze);
    Array<MazeMesh*> meshes;
    maker->SetPrimitiveType(primitiveType);
    maker->MakeMeshes(meshes);
    std::cout << "BasicMeshMaker::MakeMeshes() Successfully complete" << std::endl;
    
    // Convert the wall's MazeMesh into the engine's mesh and apply a material to it.
    mazeMeshToEngineMesh(meshes[0], &mesh1, primitiveType, Game1App::WallDiffuseFilename);
    
	// Convert the floor's MazeMesh into the engine's mesh and apply a material to it.
    mazeMeshToEngineMesh(meshes[1], &mesh2, primitiveType, Game1App::FloorDiffuseFilename );
    
    // Convert the ceiling's MazeMesh into the engine's mesh and apply a material to it.
    mazeMeshToEngineMesh(meshes[2], &mesh3, primitiveType, Game1App::CeilingDiffuseFilename);
    
	// Create a bounding volume hierarchy for the maze:
    SceneObject* b = scene->AddSceneObject("boxes");
    b->SetMeshVisible(false);
    b->SetBVHVisible( Game1App::ShowBVH );
    std::cout << "MazeBVH:: Creating bounding volume." << std::endl;
    b->SetBVH(MazeBVH::CreateBoundingVolumeHierarchy(maker));
    std::cout << "MazeBVH:: Done." << std::endl;
    
	// Iterate through all the ExternalMeshDiggers to load OBJ meshes into the scene.
    for ( i = 0; i < diggers.size(); i++) {
		ExternalMeshDigger* digger = dynamic_cast<ExternalMeshDigger*>(diggers[i]);
		if (digger != NULL) {
			int count = 0;
			ExternalMesh* xMeshes = digger->GetExternalMeshes(&count);
			
			// For each external mesh. Load the mesh, rotate it, then translate it.
			for (int j = 0; j < count; j++)
			{
				Mesh* xMesh = Mesh::CreateFromOBJFile(xMeshes[j].filename);
				xMesh->RotateVertices(xMeshes[j].rotation);
				xMesh->TranslateVertices(xMeshes[j].position);
				xMesh->SetTwoSided(true);
				scene->AddSceneObject("externalMesh", xMesh);
			}
		}
	}

	// Delete all the allocations made in this method call.
    std::cout << "Deleting resources..." << std::endl;
    for (i = 0; i < meshes.size(); i++) delete meshes[i];
    meshes.clear();
    delete maker;
    delete maze;
}

void Game1Logic::mazeMeshToEngineMesh(MazeMesh* mazeMesh, Mesh** meshRef, GLenum primitiveType, const String& diffuse)
{
    Mesh* mesh = Mesh::CreateFromMazeMesh(mazeMesh);
    *meshRef = mesh;
    mesh->SetTwoSided(false);
    mesh->SetDisplayMode(MESH_TEXTURED);
    mesh->SetPrimitiveType(primitiveType);
    scene->AddSceneObject(mazeMesh->GetName(), mesh);
    File file ( diffuse );
    std::cout << "Texture:: Loading file: " <<file.GetFullname() << std::endl;
    mesh->GetMaterial()->SetDiffuse(Texture::CreateFromFile(file));
	if (mesh->GetMaterial()->GetDiffuse() != NULL)
		std::cout << "Texture:: File loaded." << std::endl;
	else std::cout << "Error applying diffuse. Maybe texture file doesn't exist?" << std::endl;
}

void Game1Logic::setUpPlayer()
{
    player = scene->AddSceneDynamic(Vector3(0.5f, 0.3f, 0.5f), Vector3(0.4f));
}

bool Game1Logic::Update()
{
    if ( Keyboard::IsClicked('R') ) {
        playing = !playing;
        player->SetVisible(!playing);
        camera->SetFreeCam(!playing);
        if (playing) glfwDisable(GLFW_MOUSE_CURSOR);
        else         glfwEnable(GLFW_MOUSE_CURSOR);
    }
    
    if (Keyboard::IsClicked('T')) {
        display = display == MESH_TEXTURED ? MESH_EDGED : MESH_TEXTURED;
        mesh1->SetDisplayMode(display);
        mesh2->SetDisplayMode(display);
        mesh3->SetDisplayMode(display);
    }
    
    if (playing)
        UpdatePlaying();
    else
        UpdateViewing();
    
    return true;
}

void Game1Logic::UpdatePlaying()
{
    Vector3 pos = player->GetTranslation();
    Vector3 pos2 = camera->Translation();
    camera->SetTranslation(-pos);
    
    // Look around
    {
        float r = 3.142f * 0.06f * Timing::GameTimeElapsed;
        Vector2 v = Mouse::GetDisplacement();
        camera-> yaw   += v.x * r;
        camera-> pitch += v.y * r;
        
        if (camera->pitch >  3.142f/2) camera->pitch =  3.142f/2;
        if (camera->pitch < -3.142f/2) camera->pitch = -3.142f/2;
    }
    
    // Move player
    {
        Quaternion q = Quaternion ( Vector3( 0, camera->yaw, 0 ) );
        Vector3 t;
        float s = 2;
        
        if ( Keyboard::IsPressed('W') ) {
            t = Vector3 ( 0, 0, -s * Timing::GameTimeElapsed ) * q;
            player->Translate(t);
        }
        if ( Keyboard:: IsPressed('S') ) {
            t = Vector3 ( 0, 0, s * Timing::GameTimeElapsed ) * q;
            player->Translate(t);
        }
        if ( Keyboard::IsPressed('A') ) {
            t = Vector3 ( -s * Timing::GameTimeElapsed, 0, 0 ) * q;
            player->Translate(t);
        }
        if ( Keyboard:: IsPressed('D') ) {
            t = Vector3 ( s * Timing::GameTimeElapsed, 0, 0 ) * q;
            player->Translate(t);
        }
    }
}

void Game1Logic::UpdateViewing()
{
    if ( Keyboard::IsPressed('Y') ) {
        player->Translate(0, 0, 2 * Timing::GameTimeElapsed);
    }
    if ( Keyboard:: IsPressed('H') ) {
        player->Translate(0, 0,-2 * Timing::GameTimeElapsed);
    }
    if ( Keyboard::IsPressed('G') ) {
        player->Translate( 2 * Timing::GameTimeElapsed, 0, 0);
    }
    if ( Keyboard:: IsPressed('J') ) {
        player->Translate(-2 * Timing::GameTimeElapsed, 0, 0);
    }
}

int Game1Logic::End()
{
    scene->SetActiveCamera(NULL);
    delete camera;
    
    return 0;
}
