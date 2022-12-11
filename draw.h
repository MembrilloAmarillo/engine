/* date = December 12th 2022 0:53 am */

#ifndef DRAW_H
#define DRAW_H

void translate_triangle( glm::vec3& translate, uint32_t shader_id );

void rotate_triangle( glm::vec3& rotate, float angle, uint32_t shader_id );

void scale_triangle(glm::vec3& scale, uint32_t shader_id);

void perspective_projection(float angle, int width, int height, glm::vec3& motion, uint32_t shader_id);

struct Camera {
    
	glm::vec3 camera_position;
	glm::vec3 camera_target;
	glm::vec3 camera_direction;
	glm::vec3 camera_right;
	glm::vec3 camera_up;
	glm::mat4 view;
    
    glm::vec3 last_input;
    
	void init_camera();
    
	void translate_input(glm::vec3 input);
    
	void to_shader(uint32_t shader_id);
    
};

#endif //DRAW_H
