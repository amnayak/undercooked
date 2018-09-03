#pragma once

#include "GL.hpp"

#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

#include <vector>
#include <random>

// The 'Game' struct holds all of the game-relevant state,
// and is called by the main loop.

struct Game {
	//Game creates OpenGL resources (i.e. vertex buffer objects) in its
	//constructor and frees them in its destructor.
	Game();
	~Game();

	//handle_event is called when new mouse or keyboard events are received:
	// (note that this might be many times per frame or never)
	//The function should return 'true' if it handled the event.
	bool handle_event(SDL_Event const &evt, glm::uvec2 window_size);

    void update (float elapsed);

    void draw(glm::uvec2 drawable_size);

    //converts coordinates from 2D to 1D
    size_t to1D(size_t x, size_t y);

    //generate game data, fill structs
    void generate_game_data();

    //update the chef's position in the board mesh and in the game state
    //parameters are the change in x and y!
    void update_chef_loc(uint32_t x, uint32_t y);

	//------- opengl resources -------

	//shader program that draws lit objects with vertex colors:
	struct {
		GLuint program = -1U; //program object

		//uniform locations:
		GLuint object_to_clip_mat4 = -1U;
		GLuint object_to_light_mat4x3 = -1U;
		GLuint normal_to_light_mat3 = -1U;
		GLuint sun_direction_vec3 = -1U;
		GLuint sun_color_vec3 = -1U;
		GLuint sky_direction_vec3 = -1U;
		GLuint sky_color_vec3 = -1U;

		//attribute locations:
		GLuint Position_vec4 = -1U;
		GLuint Normal_vec3 = -1U;
		GLuint Color_vec4 = -1U;
	} simple_shading;

	//mesh data, stored in a vertex buffer:
	GLuint meshes_vbo = -1U; //vertex buffer holding mesh data

	//The location of each mesh in the meshes vertex buffer:
	struct Mesh {
		GLint first = 0;
		GLsizei count = 0;
	};

	Mesh tile_mesh;
	Mesh peanut_mesh;
	Mesh jelly_mesh;
	Mesh bread_mesh;
	Mesh serve_mesh;
	Mesh chef_mesh;
	Mesh counter_mesh;

	GLuint meshes_for_simple_shading_vao = -1U; //vertex array object that describes how to connect the meshes_vbo to the simple_shading_program

	//------- game state -------
    std::mt19937 mt;
	glm::uvec2 board_size = glm::uvec2(5,5);
	std::vector< Mesh const * > board_meshes;
    std::vector< Mesh const * > meshes;

	struct {
		bool roll_left = false;
		bool roll_right = false;
		bool roll_up = false;
		bool roll_down = false;
	} controls;
    struct {
        size_t p = 0;
        size_t b = 0;
        size_t j = 0;
    } inventory;

    //game data for item locations
    glm::uvec2 p_loc = glm::vec2(1,4);
    glm::uvec2 b_loc = glm::vec2(3,4);
    glm::uvec2 j_loc = glm::vec2(0,1);
    glm::uvec2 serve_loc = glm::vec2(3,0);

    glm::uvec2 p_pickup = glm::vec2(1,4);
    glm::uvec2 b_pickup = glm::vec2(3,4);
    glm::uvec2 j_pickup = glm::vec2(0,1);
    glm::uvec2 serve_pickup = glm::vec2(3,0);

    glm::uvec2 chef_loc = glm::vec2(2,2);
};
