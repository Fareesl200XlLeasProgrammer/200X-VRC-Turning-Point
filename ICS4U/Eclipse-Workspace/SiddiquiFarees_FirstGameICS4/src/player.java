import processing.core.*;
/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Farees
 */
public class player {
   public static int x, y, speed, health;
    protected final PApplet pp;
        
        boolean[] keys = new boolean[5];
        
        
        player(int x1, int y1, int speed1, PApplet applet){
            this.pp = applet;
            this.health = 300;
            this.x = x1;
            this.y = y1;
            this.speed = speed1;
        }
        
        void update(){
        	if(keys[1] == true)
                this.y = y-speed;
            
            if(keys[2] == true)
                this.x = x-speed;
                
            if(keys[3] == true)
                this.y = y+speed;
            
            if(keys[4] == true)
                this.x = x+speed;
            pp.ellipse(this.x, this.y, 50, 50);

        }
        
        void keyp(){
            if(pp.key == 'w')
                keys[1] = true;
            
            if(pp.key == 'a')
                keys[2] = true;
            
            if(pp.key == 's')
                keys[3] = true;
            
            if(pp.key == 'd')
                keys[4] = true;
        }
        
        void keyr(){
            if(pp.key == 'w')
                keys[1] = false;
            
            if(pp.key == 'a')
                keys[2] = false;
            
            if(pp.key == 's')
                keys[3] = false;
            
            if(pp.key == 'd')
                keys[4] = false;
        }
    
}
