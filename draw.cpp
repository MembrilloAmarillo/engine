

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

  matrix = glm::rotate( matrix, angle, rotate );

  GLint rotation = glGetUniformLocation( shader_id, "rotation" );
      
  glUniformMatrix4fv(
		     rotation,
		     1,
		     GL_FALSE,
		     glm::value_ptr( matrix )
		     );
}
