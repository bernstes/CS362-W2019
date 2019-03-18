/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

import junit.framework.TestCase;

/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision$
 */
public class UrlValidatorTest extends TestCase {

   private final boolean printStatus = false;
   private final boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.

   public UrlValidatorTest(String testName) {
      super(testName);
   }

   @Override
protected void setUp() {
      for (int index = 0; index < testPartsIndex.length - 1; index++) {
         testPartsIndex[index] = 0;
      }
   }

   /**
    * Create set of tests by taking the testUrlXXX arrays and
    * running through all possible permutations of their combinations.
    *
    * @param testObjects Used to create a url.
    */
   /*
   public void testIsValid(Object[] testObjects, long options) {
      UrlValidator urlVal = new UrlValidator(null, null, options);
      assertTrue(urlVal.isValid("http://www.google.com"));
      assertTrue(urlVal.isValid("http://www.google.com/"));
      int statusPerLine = 60;
      int printed = 0;
      if (printIndex)  {
         statusPerLine = 6;
      }
      do {
          StringBuilder testBuffer = new StringBuilder();
         boolean expected = true;
         for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
            int index = testPartsIndex[testPartsIndexIndex];
            ResultPair[] part = (ResultPair[]) testObjects[testPartsIndexIndex];
            testBuffer.append(part[index].item);
            expected &= part[index].valid;
         }
         String url = testBuffer.toString();
         boolean result = urlVal.isValid(url);
         assertEquals(url, expected, result);
         if (printStatus) {
            if (printIndex) {
               System.out.print(testPartsIndextoString());
            } else {
               if (result == expected) {
                  System.out.print('.');
               } else {
                  System.out.print('X');
               }
            }
            printed++;
            if (printed == statusPerLine) {
               System.out.println();
               printed = 0;
            }
         }
      } while (incrementTestPartsIndex(testPartsIndex, testObjects));
      if (printStatus) {
         System.out.println();
      }
   }
*/

    //Scheme Partition - Allow All Schemes
    public void testYourFirstPartition() {
        System.out.println("\nPartition Testing Scheme:");
        String[] validSchemes = {"http", "ftp", "h3t", "g0-to+."};
        UrlValidator validScheme = new UrlValidator(validSchemes, UrlValidator.ALLOW_ALL_SCHEMES);
        boolean result;
        for (int i = 0; i < validSchemes.length; i++) {
            result = validScheme.isValidScheme(validSchemes[i]);
            System.out.println("\nTesting Valid Scheme: " + validSchemes[i]);
            System.out.println("Expect: Pass");
            if(result){
                System.out.println("Actual: Pass");
            } else {
                System.out.println("Actual: Fail");
            }
        }

        String[] invalidSchemes = {"3ht://", "http:", "http:/", "://"};
        UrlValidator invalidScheme = new UrlValidator(invalidSchemes, UrlValidator.ALLOW_ALL_SCHEMES);
        for (int i = 0; i < invalidSchemes.length; i++) {
            result = invalidScheme.isValidScheme(invalidSchemes[i]);
            System.out.println("\nTesting Invalid Scheme: " + invalidSchemes[i]);
            System.out.println("Expect: Fail");
            if (result) {
                System.out.println("Actual: Pass");
            } else {
                System.out.println("Actual: Fail");
            }
        }
    }

    //Authority Partition
    public void testYourSecondPartition() {
        System.out.println("\nPartition Testing Authority:");
        String[] validAuths = {"www.google.com", "www.google.com.", "go.com", "255.255.255.255"};
        UrlValidator validAuth = new UrlValidator(validAuths, 0);
        boolean result;
        for (int i = 0; i < validAuths.length; i++) {
            result = validAuth.isValidAuthority(validAuths[i]);
            System.out.println("\nTesting Valid Scheme: " + validAuths[i]);
            System.out.println("Expect: Pass");
            if(result){
                System.out.println("Actual: Pass");
            } else {
                System.out.println("Actual: Fail");
            }
        }

        String[] invalidAuths = {"", "1.2.3", ".aaa", "go.a1a"};
        UrlValidator invalidAuth = new UrlValidator(invalidAuths, 0);
        for (int i = 0; i < invalidAuths.length; i++) {
            result = invalidAuth.isValidAuthority(invalidAuths[i]);
            System.out.println("\nTesting Invalid Scheme: " + invalidAuths[i]);
            System.out.println("Expect: Fail");
            if (result) {
                System.out.println("Actual: Pass");
            } else {
                System.out.println("Actual: Fail");
            }
        }
    }

    //Port Partition - use know valid authorities with valid/invalid ports
    public void testYourThirdPartition() {
        System.out.println("\nPartition Testing Authority + Port:");
        String[] validAuths = {"www.google.com", "www.google.com.", "go.com", "255.255.255.255"};
        String[] validPorts = {":65535", ":0", ":80", ""};
        boolean result;
        for (int i = 0; i < validAuths.length; i++){
            String combo = validAuths[i] + validPorts[i];
            UrlValidator validPort = new UrlValidator();
            result = validPort.isValidAuthority(combo);
            System.out.println("\nTesting Valid Authority + Valid Port: " + combo);
            System.out.println("Expect: Pass");
            if(result){
                System.out.println("Actual: Pass");
            } else {
                System.out.println("Actual: Fail");
            }
        }

        String[] invalidPorts = {":-1", ":66666", ":80a", "::"};
        for (int i = 0; i < validAuths.length; i++){
            String combo = validAuths[i] + invalidPorts[i];
            UrlValidator invalidPort = new UrlValidator();
            result = invalidPort.isValidAuthority(combo);
            System.out.println("\nTesting Valid Authority + Invalid Port: " + combo);
            System.out.println("Expect: Fail");
            if(result){
                System.out.println("Actual: Pass");
            } else {
                System.out.println("Actual: Fail");
            }
        }
    }

    //Path Partition - Allow 2 Slashes
    public void testYourFourthPartition() {
        System.out.println("\nPartition Testing Path:");
        String[] validPaths = {"/t123", "/$23", "/test1//file", "/file", ""};
        UrlValidator validPath = new UrlValidator(validPaths, UrlValidator.ALLOW_2_SLASHES);
        boolean result;
        for (int i = 0; i < validPaths.length; i++) {
            result = validPath.isValidPath(validPaths[i]);
            System.out.println("\nTesting Valid Path: " + validPaths[i]);
            System.out.println("Expect: Pass");
            if(result){
                System.out.println("Actual: Pass");
            } else {
                System.out.println("Actual: Fail");
            }
        }

        String[] invalidPaths = {"/..", "/#", "/../file", "/../"};
        UrlValidator invalidPath = new UrlValidator(invalidPaths, UrlValidator.ALLOW_2_SLASHES);
        for (int i = 0; i < invalidPaths.length; i++) {
            result = invalidPath.isValidPath(invalidPaths[i]);
            System.out.println("\nTesting Invalid Path: " + invalidPaths[i]);
            System.out.println("Expect: Fail");
            if(result){
                System.out.println("Actual: Pass");
            } else {
                System.out.println("Actual: Fail");
            }
        }
    }

    //Query Partition
    public void testYourFifthPartition(){
        System.out.println("\nPartition Testing Query:");
        String[] validQueries = {"?action=view", "?action=edit", "?action=edit&mode=up", ""};
        UrlValidator validQuery = new UrlValidator(validQueries, 0);
        boolean result;
        for (int i = 0; i < validQueries.length; i++) {
            result = validQuery.isValidQuery(validQueries[i]);
            System.out.println("\nTesting Valid Query: " + validQueries[i]);
            System.out.println("Expect: Pass");
            if(result){
                System.out.println("Actual: Pass");
            } else {
                System.out.println("Actual: Fail");
            }
        }
    }

    public void testIsValidProgramming()
    {
        //Testing URLs using programming-based testing
        System.out.println("\nProgramming-Based Testing\n");
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
            Boolean isValid = urlVal.isValid(invalidUrls[i]);
            if (isValid == true)
            {
                s.append("URL VALIDATOR FAILED: ");
            }
            s.append("Url tested was: " + invalidUrls[i] + " The expect result was false\n");
            String out = s.toString();
            System.out.println(out);
        }

    }

    static boolean incrementTestPartsIndex(int[] testPartsIndex, Object[] testParts) {
      boolean carry = true;  //add 1 to lowest order part.
      boolean maxIndex = true;
      for (int testPartsIndexIndex = testPartsIndex.length - 1; testPartsIndexIndex >= 0; --testPartsIndexIndex) {
         int index = testPartsIndex[testPartsIndexIndex];
         ResultPair[] part = (ResultPair[]) testParts[testPartsIndexIndex];
         maxIndex &= (index == (part.length - 1));
         if (carry) {
            if (index < part.length - 1) {
               index++;
               testPartsIndex[testPartsIndexIndex] = index;
               carry = false;
            } else {
               testPartsIndex[testPartsIndexIndex] = 0;
               carry = true;
            }
         }
      }


      return (!maxIndex);
   }

   private String testPartsIndextoString() {
       StringBuilder carryMsg = new StringBuilder("{");
      for (int testPartsIndexIndex = 0; testPartsIndexIndex < testPartsIndex.length; ++testPartsIndexIndex) {
         carryMsg.append(testPartsIndex[testPartsIndexIndex]);
         if (testPartsIndexIndex < testPartsIndex.length - 1) {
            carryMsg.append(',');
         } else {
            carryMsg.append('}');
         }
      }
      return carryMsg.toString();

   }

   //-------------------- Test data for creating a composite URL
   /**
    * The data given below approximates the 4 parts of a URL
    * <scheme>://<authority><path>?<query> except that the port number
    * is broken out of authority to increase the number of permutations.
    * A complete URL is composed of a scheme+authority+port+path+query,
    * all of which must be individually valid for the entire URL to be considered
    * valid.
    */
   ResultPair[] testUrlScheme = {new ResultPair("http://", true),
                               new ResultPair("ftp://", true),
                               new ResultPair("h3t://", true),
                               new ResultPair("3ht://", false),
                               new ResultPair("http:/", false),
                               new ResultPair("http:", false),
                               new ResultPair("http/", false),
                               new ResultPair("://", false)};

   ResultPair[] testUrlAuthority = {new ResultPair("www.google.com", true),
                                  new ResultPair("www.google.com.", true),
                                  new ResultPair("go.com", true),
                                  new ResultPair("go.au", true),
                                  new ResultPair("0.0.0.0", true),
                                  new ResultPair("255.255.255.255", true),
                                  new ResultPair("256.256.256.256", false),
                                  new ResultPair("255.com", true),
                                  new ResultPair("1.2.3.4.5", false),
                                  new ResultPair("1.2.3.4.", false),
                                  new ResultPair("1.2.3", false),
                                  new ResultPair(".1.2.3.4", false),
                                  new ResultPair("go.a", false),
                                  new ResultPair("go.a1a", false),
                                  new ResultPair("go.cc", true),
                                  new ResultPair("go.1aa", false),
                                  new ResultPair("aaa.", false),
                                  new ResultPair(".aaa", false),
                                  new ResultPair("aaa", false),
                                  new ResultPair("", false)
   };
   ResultPair[] testUrlPort = {new ResultPair(":80", true),
                             new ResultPair(":65535", true), // max possible
                             new ResultPair(":65536", false), // max possible +1
                             new ResultPair(":0", true),
                             new ResultPair("", true),
                             new ResultPair(":-1", false),
                             new ResultPair(":65636", false),
                             new ResultPair(":999999999999999999", false),
                             new ResultPair(":65a", false)
   };
   ResultPair[] testPath = {new ResultPair("/test1", true),
                          new ResultPair("/t123", true),
                          new ResultPair("/$23", true),
                          new ResultPair("/..", false),
                          new ResultPair("/../", false),
                          new ResultPair("/test1/", true),
                          new ResultPair("", true),
                          new ResultPair("/test1/file", true),
                          new ResultPair("/..//file", false),
                          new ResultPair("/test1//file", false)
   };
   //Test allow2slash, noFragment
   ResultPair[] testUrlPathOptions = {new ResultPair("/test1", true),
                                    new ResultPair("/t123", true),
                                    new ResultPair("/$23", true),
                                    new ResultPair("/..", false),
                                    new ResultPair("/../", false),
                                    new ResultPair("/test1/", true),
                                    new ResultPair("/#", false),
                                    new ResultPair("", true),
                                    new ResultPair("/test1/file", true),
                                    new ResultPair("/t123/file", true),
                                    new ResultPair("/$23/file", true),
                                    new ResultPair("/../file", false),
                                    new ResultPair("/..//file", false),
                                    new ResultPair("/test1//file", true),
                                    new ResultPair("/#/file", false)
   };

   ResultPair[] testUrlQuery = {new ResultPair("?action=view", true),
                              new ResultPair("?action=edit&mode=up", true),
                              new ResultPair("", true)
   };

   Object[] testUrlParts = {testUrlScheme, testUrlAuthority, testUrlPort, testPath, testUrlQuery};
   Object[] testUrlPartsOptions = {testUrlScheme, testUrlAuthority, testUrlPort, testUrlPathOptions, testUrlQuery};
   int[] testPartsIndex = {0, 0, 0, 0, 0};

   //---------------- Test data for individual url parts ----------------
   private final String[] schemes = {"http", "gopher", "g0-To+.",
                                      "not_valid" // TODO this will need to be dropped if the ctor validates schemes
                                    };

   ResultPair[] testScheme = {new ResultPair("http", true),
                            new ResultPair("ftp", false),
                            new ResultPair("httpd", false),
                            new ResultPair("gopher", true),
                            new ResultPair("g0-to+.", true),
                            new ResultPair("not_valid", false), // underscore not allowed
                            new ResultPair("HtTp", true),
                            new ResultPair("telnet", false)};


}

