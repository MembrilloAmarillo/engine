void translate_triangle( glm::vec3& translate, uint32_t shader_id )
{
    glm::mat4 matrix( 1.0f );
    
    matrix = glm::translate( matrix, translate );
    
    GLint transform = glGetUniformLocation( shader_id, "translation" );
    
    glUniformMatrix4fv(
                       transform,
                       1,
                       GL_FALSE,
                       glm::value_ptr( matrix )
                       );
    
}

void rotate_triangle( glm::vec3& rotate, float angle, uint32_t shader_id )
{
    glm::mat4 matrix( 1.0f );
    
    if (angle != 0 && (rotate.x != 0 || rotate.y != 0 || rotate.z != 0)) {
        matrix = glm::rotate(matrix, angle, rotate);
    }
    
    GLint rotation = glGetUniformLocation( shader_id, "rotation" );
    
    glUniformMatrix4fv(
                       rotation,
                       1,
                       GL_FALSE,
                       glm::value_ptr( matrix )
                       );
}

void scale_triangle(glm::vec3& scale, uint32_t shader_id)
{
    glm::mat4 matrix(1.0f);
    
    if( scale.x != 0 || scale.y != 0 || scale.z != 0 ) {
        matrix = glm::scale( matrix, scale );
    }
    GLint scalation = glGetUniformLocation( shader_id, "scale" );
    
    glUniformMatrix4fv(
                       scalation,
                       1,
                       GL_FALSE,
                       glm::value_ptr( matrix )
                       );
}

void perspective_projection(float angle, float width, float height, glm::vec3& motion, uint32_t shader_id)
{
	glm::mat4 projection = glm::perspective(
                                            glm::radians( angle ),
                                            width / height,
                                            0.1f,
                                            100.0f);
    glm::mat4 matrix( 1.0f );
    matrix= glm::translate( matrix, motion );
    
    projection = matrix * projection;
    
	GLint proj = glGetUniformLocation(shader_id, "projection");
	glUniformMatrix4fv(
                       proj,
                       1,
                       GL_FALSE,
                       glm::value_ptr( projection )
                       );
}

struct Camera {
    
	glm::vec3 camera_position;
	glm::vec3 camera_target;
	glm::vec3 camera_direction;
	glm::vec3 camera_right;
	glm::vec3 camera_up;
	glm::mat4 view;
    
    glm::vec3 last_input;
    
	void init_camera() {
		camera_position  = glm::vec3(0.0f, 0.0f, 3.0f);
		camera_target    = glm::vec3(0.0f, 0.0f, 0.0f);
		camera_direction = glm::normalize(camera_position - camera_target);
		
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		camera_right = glm::normalize(glm::cross(up, camera_direction));
        
		camera_up = glm::cross(camera_direction, camera_right);
        
		view = glm::lookAt(glm::vec3(0.0f, 0.0f, 3.0f),
		                   glm::vec3(0.0f, 0.0f, 0.0f),
		                   glm::vec3(0.0f, 1.0f, 0.0f));
        last_input = glm::vec3(0.0f, 1.0f, 0.0f); 
	}
    
	void translate_input(glm::vec3 input) {
        if( input != last_input ) {
            view = glm::translate(view, input);
            last_input = input;
        }
	}
    
	void to_shader(uint32_t shader_id) {
		GLint camera_view = glGetUniformLocation(shader_id, "view");
        
		glUniformMatrix4fv( camera_view,
		                   1,
		                   GL_FALSE,
		                   glm::value_ptr( view )
		                   );                   
	}
    
};