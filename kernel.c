void dummy_test_entrypoint(){

}

void main() {
  char * video_mem = (char*) 0xb8000;
  *video_mem = 'X';
  video_mem++;
  *video_mem = 'O';
}