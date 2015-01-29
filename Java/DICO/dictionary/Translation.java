package dictionary;

public class Translation {
	private String first;
	private String second;
	
	
	public Translation(String first, String second) {
		super();
		this.first = first;
		this.second = second;
	}


	boolean isTranslate(String word){
		return (word.equals(first) || word.equals(second));
	}
	
	String getTranslate(String word){
		if(first.equals(word)){
			return second;
		}
		return first;
	}
}
