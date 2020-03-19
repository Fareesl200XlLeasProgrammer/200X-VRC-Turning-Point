import processing.core.*;
import java.util.Random; 

public class Main extends PApplet{
	
	int screen = 0;
	public static player player;
	
	float x;
	float y;
	double easing = 0.03;

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		PApplet.main("Main");
	}
	
	@Override
	public void settings() {
		size(3840, 2160);
		player = new player(350, 870, 5, this);
	}
	
	@Override
    public void setup(){

    }
    
    @Override
    public void draw(){    	  
    	player.update();
    }
    
    @Override
    public void keyPressed() {
    	player.keyp();
    }
    
    @Override
    public void keyReleased() {
    	player.keyr();
    }
	

}
