int variable = 0;
void setup(){
  size(800,600);
}

void draw(){

}

void mouseDragged() {

  stroke(variable);
  //point(mouseX,mouseY);
  line(mouseX, mouseY, pmouseX, pmouseY);
}

void keyPressed() {
  if ( key >= '0' && key <= '9' ) {
    int i = int(key);
    variable = (i - 48) * 28;
  }
}
