#include "graph.h"



///
///

cx::simulation::graph::graph(float rate, cx::engine::environment* engine, cx::engine::eventing* events) : cx::engine::base::eventable(events), cx::engine::base::scene() {
    // Set the reference to the SDL and OpenGL environment this scene renders into.
    this->engine = engine;
    this->function.getFunction();
    
    this->rate = rate;

    // Call the resource initialisation subroutines.
    initialise_camera();
    initialise_programs();
    initialise_renderables();
    initialise_lights();

    //Start the timer
    this->ftimer.reset_start();

    // Set up eventing.
    events->hook(SDL_CX_IDLEEVENT, this);
    events->hook(SDL_CX_MOVEEVENT, this);
}



///
///

void cx::simulation::graph::render(){
    // Set up the programmable pipeline program.
    glUseProgram(this->programs[0]->get_id());

    // Create the transformation matrices.
    glm::mat4 model;
    glm::mat4 view = camera->get_transformation();
    glm::mat4 projection = (glm::mat4)glm::perspective(45.0, (double) this->engine->get_aspect_ratio(), 1.0, 256.0);
    glm::mat3 modelview_invtrans;
    
     // Create the modelview transformation.
        glm::mat4 modelview;
        model = (*renderables.begin())->get_transformation();
        modelview = view * model;
        modelview_invtrans = glm::inverse(glm::transpose(glm::mat3(modelview)));

    // Iterate over all renderable objects.
    for (std::vector<cx::engine::base::renderable*>::iterator i = renderables.begin(); i != renderables.end(); i++) {
       

        // Send the transformations to the programmable pipeline.
        glUniformMatrix4fv(uniforms[0].mat4_modelview, 1, GL_FALSE, glm::value_ptr(modelview));
        glUniformMatrix4fv(uniforms[0].mat4_projection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix3fv(uniforms[0].mat3_modelview_invtrans, 1, GL_FALSE, glm::value_ptr(modelview_invtrans));
        
        glUniform1f (uniforms[0].float_time,ftimer.get_total_time());
        glUniform1f (uniforms[0].float_rate,rate);
        
        light->send_uniforms(modelview);

        // Call the rendering subroutine for this renderable object.
        (*i)->render((void*) &attributes[0]);
    }
        glUseProgram(this->programs[1]->get_id());
     // Send the transformations to the programmable pipeline.
        glUniformMatrix4fv(uniforms[1].mat4_modelview, 1, GL_FALSE, glm::value_ptr(modelview));
        glUniformMatrix4fv(uniforms[1].mat4_projection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix3fv(uniforms[1].mat3_modelview_invtrans, 1, GL_FALSE, glm::value_ptr(modelview_invtrans));
        
        glUniform1f (uniforms[1].float_time,ftimer.get_total_time());
        glUniform1f (uniforms[1].float_rate,rate);
        
      /*  glBindBuffer( GL_ARRAY_BUFFER, static_cast<cx::simulation::chunk*>((*renderables.begin()))->buffers_vertex[0]->get_id() );
	glEnableVertexAttribArray( attributes[1].vec4_position );
	glEnableVertexAttribArray( attributes[1].vec4_colour );
        glEnableVertexAttribArray( attributes[1].vec4_normal );
	glVertexAttribPointer( attributes[1].vec4_position, 4, GL_FLOAT, GL_FALSE, sizeof( cx::simulation::chunk::vertex ), (void*)offsetof( cx::simulation::chunk::vertex, position ) );
	glVertexAttribPointer( attributes[1].vec4_colour,    4, GL_FLOAT, GL_FALSE, sizeof( cx::simulation::chunk::vertex ), (void*)offsetof( cx::simulation::chunk::vertex, colour ) );
        glVertexAttribPointer( attributes[1].vec4_normal,    4, GL_FLOAT, GL_FALSE, sizeof( cx::simulation::chunk::vertex ), (void*)offsetof( cx::simulation::chunk::vertex, normal ) );
        int N = std::pow( 2.0, 10) + 1;
        glDrawArrays (GL_POINTS, 0, N*N);
        */
    
    // Tell SDL to display the contents of the OpenGL rendered scene.
    SDL_GL_SwapBuffers();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
}

void cx::simulation::graph::on_idle(SDL_Event event) {
    //Get time between frames
    GLuint time_elapsed = this->ftimer.get_time_elapsed();
    //Move camera appropriately
    this->camera->update(time_elapsed);
    //Render scene
    this->render();
    //Count FPS
    this->fps.countfps();
    
    
}



///
///

void cx::simulation::graph::on_move(SDL_Event event) {
    // Ascertain the new position of the camera.
    glm::vec3 position = *(glm::vec3*)event.user.data1;
}



///
///

void cx::simulation::graph::delegate(SDL_Event event) {
    if (event.type == SDL_USEREVENT) std::cerr << "idle" << std::endl;

    // Call the correct function based on the type of event.
    switch (event.type) {
        case SDL_CX_IDLEEVENT: on_idle(event);
            break;
        case SDL_CX_MOVEEVENT: on_move(event);
            break;
    }
}



///
///

void cx::simulation::graph::initialise_camera() {
    // Set up a static camera.
    this->camera = new cx::engine::flying_camera(glm::vec3(-10.0, 0.0, 0.0), glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0, 0.0, 1.0), events);
}



///
///

void cx::simulation::graph::initialise_programs() {
    // Create the vertex and fragment shaders.
    cx::engine::pipeline::shader basic_fragment(GL_FRAGMENT_SHADER, "glsl/basic.fragment.glsl",false);
    cx::engine::pipeline::shader basic_vertex(GL_VERTEX_SHADER, "glsl/basic.vertex.glsl",false);
    cx::engine::pipeline::shader norm_fragment(GL_FRAGMENT_SHADER, "glsl/normal.fragment.glsl",false);
    cx::engine::pipeline::shader norm_vertex(GL_VERTEX_SHADER, "glsl/normal.vertex.glsl",false);

    // Build the shaders into a program.
    cx::engine::pipeline::program* basic = new cx::engine::pipeline::program({basic_vertex, basic_fragment});
    cx::engine::pipeline::program* normal = new cx::engine::pipeline::program({norm_vertex, norm_fragment});
    this->programs.push_back(basic);
    this->programs.push_back(normal);
    // Set up the attributes and uniforms passed to the programmable pipeline.
    this->attributes[0].vec4_position = this->programs[0]->bindAttribute("position");
    this->attributes[0].vec4_colour = this->programs[0]->bindAttribute("colour");
    this->attributes[0].vec4_normal = this->programs[0]->bindAttribute("normal");
    this->uniforms[0].mat4_modelview = this->programs[0]->bindUniform("modelview");
    this->uniforms[0].mat4_projection = this->programs[0]->bindUniform("projection");
    this->uniforms[0].mat3_modelview_invtrans = this->programs[0]->bindUniform("modelview_invtrans");
    this->uniforms[0].float_time = this->programs[0]->bindUniform("time");
    this->uniforms[0].float_rate = this->programs[0]->bindUniform("rate");
    this->attributes[1].vec4_position = this->programs[1]->bindAttribute("position");
    this->attributes[1].vec4_colour = this->programs[1]->bindAttribute("colour");
    this->attributes[1].vec4_normal = this->programs[1]->bindAttribute("normal");
    this->uniforms[1].mat4_modelview = this->programs[1]->bindUniform("modelview");
    this->uniforms[1].mat4_projection = this->programs[1]->bindUniform("projection");
    this->uniforms[1].mat3_modelview_invtrans = this->programs[1]->bindUniform("modelview_invtrans");
    this->uniforms[1].float_time = this->programs[1]->bindUniform("time");
    this->uniforms[1].float_rate = this->programs[1]->bindUniform("rate");
}



///
///

void cx::simulation::graph::initialise_renderables() {
    // Specify the correct format for a chunk.
    cx::simulation::chunk::specification.function = this->function;
    cx::simulation::chunk::specification.levels_of_detail = 2;
    cx::simulation::chunk::specification.resolution = 10;
    cx::simulation::chunk::specification.scale_data = 0.02;
    cx::simulation::chunk::specification.scale_world = 0.025;

    // Create the parameters for a test chunk.
    chunk::local_parameters p;
    p.center = glm::vec2(0.0, 0.0);

    // Push the test chunk onto the renderables list.
    cx::simulation::chunk* c = new cx::simulation::chunk(p, this);
    this->renderables.push_back(c);
}


void cx::simulation::graph::initialise_lights() {
    cx::engine::light::parameters params;
    params.name = "light0";
    params.linearAttenuation =1.0f;
    params.position = glm::vec4 (0.0,0.0,100.0,1.0);
    params.diffuse = glm::vec4(1.0,  1.0,  1.0, 1.0);
    params.specular = glm::vec4(0.25,  0.25,  0.25, 0.25);
    this->light = new cx::engine::light (params);
    this->light->bind_uniforms((*this->programs[0]));
}