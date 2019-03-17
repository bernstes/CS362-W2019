

import junit.framework.TestCase;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.FileReader;
import java.util.Scanner;



//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class urlValTest extends TestCase {


   public urlValTest(String testName) {
      super(testName);

   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing
      UrlValidator urlVal = new UrlValidator();
      
      Scanner reader = new Scanner(System.in);
      System.out.println("Enter the path to the CSV file containing test urls, where the first value is the url, and the second is the expected value");
      BufferedReader input = new BufferedReader(new InputStreamReader(System.in));
      String inFile = input.readLine();

      BufferedReader br = null;
      String line = "";
      String csvSplitBy = ",";


         br = new BufferedReader(new FileReader(inFile));
         while ((line = br.readLine()) != null) {
            
            String[] url = line.split(csvSplitBy);
            System.out.println("The url tested is " + url[0] + "The tested value is " + urlVal.isValid(url[0]) + " and the expect value is " + url[1]);

         }	   

}
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
}





