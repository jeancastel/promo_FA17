package dictionary;

import static org.junit.Assert.*;

import org.junit.Before;
import org.junit.Test;

public class check {

	   protected Dictionary dico;

	    @Before
	    public void setUp() {
	        dico = new Dictionary("English", "Fran�ais");
	    }

	    protected void addTranslations() {
	        dico.addTranslation("bonjour", "hello");
	        dico.addTranslation("demain", "tomorrow");
	        dico.addTranslation("chien", "dog");
	        dico.addTranslation("maison", "house");
	        dico.addTranslation("Etudiant", "student");
	    }

	    @Test
	    public void test_correctLanguages() {
	        assertFalse(dico.getLanguage("Deutsch", "Espa�ol"));
	        assertFalse(dico.getLanguage("Fran�ais", "Brezhoneg"));
	        assertTrue(dico.getLanguage("English", "Fran�ais"));
	        assertTrue(dico.getLanguage("Fran�ais", "English"));
	    }

	    @Test
	    public void test_emptyHasNoWords() {
	        assertFalse(dico.contains("bonjour"));
	    }

	    @Test
	    public void test_emptyHasZeroTranslations() {
	        assertEquals(0, dico.numberOfTranslation());
	    }

	    @Test
	    public void test_withOneTranslation() {
	        dico.addTranslation("bonjour", "hello");
	        assertEquals(1, dico.numberOfTranslation());
	        assertTrue(dico.contains("bonjour"));
	        assertTrue(dico.contains("hello"));
	        assertEquals("hello", dico.translate("bonjour"));
	        assertEquals("bonjour", dico.translate("hello"));
	    }

	    @Test
	    public void test_withManyTranslations() {
	        addTranslations();
	        assertEquals(5, dico.numberOfTranslation());
	        assertTrue(dico.contains("house"));
	        assertEquals("dog", dico.translate("chien"));
	    }

	    @Test
	    public void test_removingATranslation() {
	        addTranslations();
	        dico.removeTranslation("tomorrow");
	        assertEquals(4, dico.numberOfTranslation());
	        assertFalse(dico.contains("tomorrow"));
	        assertFalse(dico.contains("demain"));
	    }
}
