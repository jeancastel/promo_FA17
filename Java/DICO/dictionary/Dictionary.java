package dictionary;

import java.util.ArrayList;
import java.util.ListIterator;

public class Dictionary {
	private String firstLanguage, secondLanguage;
	private ArrayList<Translation> dico;
	
	
	public Dictionary(String firstLanguage, String secondLanguage) {
		super();
		this.firstLanguage = firstLanguage;
		this.secondLanguage = secondLanguage;
		this.dico = new ArrayList<Translation>();
	}

	public boolean getLanguage(String firstLanguage, String secondLanguage){
		return ((this.firstLanguage.equals(firstLanguage) && this.secondLanguage.equals(secondLanguage)) || (this.firstLanguage.equals(secondLanguage) && this.secondLanguage.equals(firstLanguage)));
	}
	
	public int numberOfTranslation(){
		return dico.size();
	}
	
	public String translate(String word){
		int idx = findWord(word);
		if(idx != -1){
			return dico.get(idx).getTranslate(word);
		}
		return "no translation find for this word";
		
	}
	
	public void removeTranslation(String word){
		int idx = findWord(word);
		if(idx != -1){
			dico.remove(idx);
		}
	}
	
	private int findWord(String word){
		ListIterator<Translation> li = dico.listIterator();
		while(li.hasNext()){
			if(li.next().isTranslate(word)){
				return li.nextIndex() -1;
			}
		}
		return -1;
	}
	
	
	public void addTranslation(Translation translation){
		dico.add(translation);
	}
	public void addTranslation(String first, String second){
		dico.add(new Translation(first, second));
	}
	
	public boolean contains(String word){
		if(findWord(word) == -1){
			return false;
		}
		return true;
	}
	
}
