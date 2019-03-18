

import junit.framework.TestCase;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.FileReader;
import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.IOException;


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

      try {

         br = new BufferedReader(new FileReader(inFile));
         while ((line = br.readLine()) != null) {
            
            String[] url = line.split(csvSplitBy);
            System.out.println("The url tested is " + url[0] + "The tested value is " + urlVal.isValid(url[0]) + " and the expect value is " + url[1]);

         }	   


      } catch (FileNotFoundException e) {
         e.printStackTrace();
      } catch (IOException e) {
         e.printStackTrace();
      } finally {
         if (br != null) {
            try {
               br.close();
            } catch (IOException e) {
               e.printStackTrace();
            }
         }
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


      UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
      String[] validUrls = {
         "http://www.google.com",
         "http://www.google.com/",
         "http://0.0.0.0/",
         "http://www.google.com/valid",
         "http://google.com/",
         "http://www.google.com/valid/valid/valid/valid/valid/valid/valid",
         "http://www.google.com/test?action=view",
         "http://www.google.com/#/",
         "http://www.google.com/23/",
         "http://www.google.net",
         "http://www.google.co.uk",
         "http://www.google.com:0",
         "http://www.google.com:6000"
      };

      String[] invalidUrls = {
         "http://www.google.xdx/",
         "http://www.google.xdx/", 
         "http://www.google.bbbbb", 
         "http://www.google.jfiekd", 
         "ftp://www.google.jfiekd/", 
         "htp:/www.google.com/", 
         "255.255.255.255", 
         "http://256.256.256.256", 
         "ftp://256.256.256.256", 
         "http://www.google.com/..//file", 
         "http://www.google.com:-1", 
         "http://www.google.com:65a", 
         "http://www.google.com/test//testfile", 
         "http://localhost/", 
         "http://machine/", 
         "http://localhost:8000",  
         "ftp://localhost:8000", 
         "http://machine:0", 
         "http://www.google.com/invalid//invalid", 
         "ftp://www.google.com/invalid//invalid", 
         "ftp://www.google.com/invalid//invalid//invalid"
      };

      for (int i = 0; i < validUrls.length; i++)
      {
         StringBuilder s = new StringBuilder();
         Boolean isValid = urlVal.isValid(validUrls[i]);
         if (isValid == false)
         {
            s.append("URL VALIDATOR FAILED: ");
         }
         s.append("Url tested was: " + validUrls[i] + "The expect result was true\n");
         String out = s.toString();
         System.out.println(out);
      }

      for (int i = 0; i < invalidUrls.length; i++)
      {
         StringBuilder s = new StringBuilder();
         Boolean isValid = urlVal.isValid(validUrls[i]);
         if (isValid == false)
         {
            s.append("URL VALIDATOR FAILED: ");
         }
         s.append("Url tested was: " + validUrls[i] + "The expect result was false\n");
         String out = s.toString();
         System.out.println(out);
      }
      
   }

   public static void main(String[] args) {
      urlValTest tester = new urlValTest("testing");
      tester.testManualTest();
      tester.testIsValid();
   }
}





