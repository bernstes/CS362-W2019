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
import java.io.*;
import java.util.Random;

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

    public void testManualTest()
    {
        //You can use this function to implement your manual testing
        System.out.println("\nManual Testing");
        UrlValidator urlVal = new UrlValidator();

        String inFile = "urltests.csv";

        BufferedReader br = null;
        String line = "";
        String csvSplitBy = ",";

        try {

            br = new BufferedReader(new FileReader(inFile));
            while ((line = br.readLine()) != null) {
                String[] url = line.split(csvSplitBy);
                System.out.println("\nThe url tested is " + url[0] + " The tested value is " + urlVal.isValid(url[0]) + " and the expect value is " + url[1]);
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

    public void testIsValidRandom()
    {

        System.out.println("\nStart random testing for valid URLs - all expected to pass\n");

        String validSchemes[] = {"http://", "https://", "ftp://", "h3t://"};
        String validAuthorities[] = {"www.apple.com", "www.google.com.", "oregonstate.edu", "123.com", "255.255.255.255", "www.navy.mil"};
        String validPorts[] = {":80", "", ":8080", ":0", ":65535"};
        String validPaths[] = {"/foo", "/f567", "/$98", "/bar/", "", "/foo/bar/"};
        String validQueries[] = {"", "?foo=bar", "?foo=bar&test=HelloWorld"};

        UrlValidator testURL = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        boolean result;
        for(int i = 0; i < 500; i++)
        {

            String scheme = validSchemes[new Random().nextInt(validSchemes.length)];
            String authority = validAuthorities[new Random().nextInt(validAuthorities.length)];
            String port = validPorts[new Random().nextInt(validPorts.length)];
            String path = validPaths[new Random().nextInt(validPaths.length)];
            String query = validQueries[new Random().nextInt(validQueries.length)];
            String random_url = scheme+authority+port+path+query;
            System.out.println("Currently Testing: " + random_url);
            result = testURL.isValid(scheme+authority+port+path+query);
            if(result){
                System.out.println("Test Passed");
            } else {
                System.out.println("Test Failed");
            }
        }

        System.out.println("End random testing for valid URLs\n");
    }

    public void testIsInvalidRandom()
    {

        System.out.println("\nStart random testing for invalid URLs - all expected to fail\n");

        String invalidSchemes[] = {"http//", "://", "http/", "https:", "3ft://", "http:/" };
        String invalidAuthorities[] = {"1.2.3", "1.2.3.4.5", "1.2.3.4.", "256.256.256.256", "aaa."};
        String invalidPorts[] = {":-9", ":75636", ":99999999999", ":12z", "4$44", ":00a"};
        String invalidPaths[] = {"/..", "/../../", "/foo//bar", "////////pathQuery#Fragment", "/../file", "/#/file"};
        String validQueries[] = {"", "?foo=bar", "?foo=bar&test=HelloWorld", "/home/index.html"};


        UrlValidator testURL = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        boolean result;
        for(int i = 0; i < 500; i++)
        {

            String scheme = invalidSchemes[new Random().nextInt(invalidSchemes.length)];
            String authority = invalidAuthorities[new Random().nextInt(invalidAuthorities.length)];
            String port = invalidPorts[new Random().nextInt(invalidPorts.length)];
            String path = invalidPaths[new Random().nextInt(invalidPaths.length)];
            String query = validQueries[new Random().nextInt(validQueries.length)];
            String random_url = scheme+authority+port+path+query;
            System.out.println("Currently Testing: " + random_url);
            result = testURL.isValid(scheme+authority+port+path+query);
            if(result){
                System.out.println("Test Passed");
            } else {
                System.out.println("Test Failed");
            }
        }

        System.out.println("\nEnd random testing for invalid URLs");
    }
}

