package org.ads.nlp;

import static org.junit.Assert.assertTrue;

import org.ads.TestUtils;
import org.junit.Test;

import java.util.Set;

public class UserInputTest extends AbstractTestCase {

  @Test
  public void testAddFinalInput() {

    UserInput userInput = new UserInput();
    assertTrue(userInput.getFinalInputs().size() == 0);

    final String random1 = TestUtils.randomString();
    userInput.addFinalInput(random1);

    final Set<String> finalInputs = userInput.getFinalInputs();
    assertTrue(finalInputs.size() == 1);
    assertTrue(finalInputs.contains(random1));

    final String random2 = TestUtils.randomString();
    userInput.addFinalInput(random2);

    assertTrue(finalInputs.size() == 2);
    assertTrue(finalInputs.contains(random2));
    
  }

  @Test
  public void testAddPrimaryInputSyn() {
    
    UserInput userInput = new UserInput();
    assertTrue(userInput.getSyns().size() == 0);

    final String random1 = TestUtils.randomString();
    userInput.addSyn  (random1);

    final Set<String> syns = userInput.getSyns();
    assertTrue(syns.size() == 1);
    assertTrue(syns.contains(random1));

    final String random2 = TestUtils.randomString();
    userInput.addSyn(random2);

    assertTrue(syns.size() == 2);
    assertTrue(syns.contains(random2));

    
  }

}