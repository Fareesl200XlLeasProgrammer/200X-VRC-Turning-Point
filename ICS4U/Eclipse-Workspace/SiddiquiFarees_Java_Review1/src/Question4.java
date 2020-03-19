import java.util.*;
public class Question4 {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		System.out.println("Enter an integer between 0 and 1000");
		Scanner inp = new Scanner(System.in);
		int num = inp.nextInt();
		int o;
		int t;
		int h;
		
		
		while(true) {
			if(num<1000 && num > 0) {
				o = (num/1)%10;
				t = (num/10)%10;
				h = (num/100)%10;
				
				System.out.println("Ones place: "+o);
				System.out.println("Tens place: "+t);
				System.out.println("Hundreds place: "+h);
				break;
			}
			else {
				System.out.println("ENETR A NUMBER BETWEEN 0 AND 1000");
				num = inp.nextInt();
			}
		}
	}

}
