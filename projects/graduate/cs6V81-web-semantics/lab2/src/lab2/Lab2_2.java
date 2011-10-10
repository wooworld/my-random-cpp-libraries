/*
 * Lab1_2e creates multiple Jena Model instances with various ways of populating
 * the data inside the model.
 *  
 * @version
 * 1.3 9/28/2011
 * 
 * @author
 * Gary Steelman
 */

package lab2;

import com.hp.hpl.jena.rdf.model.*; 
import com.hp.hpl.jena.sdb.SDBFactory;
import com.hp.hpl.jena.sdb.Store;
import com.hp.hpl.jena.vocabulary.*;
import java.io.*;

/*
 * Lab2_2 creates multiple Jena Model instances with various ways of populating
 * the data inside the model.
 */
public class Lab2_2 {
	public static void main(String[] args) {		
		// Local variables for populating the Models
		String xsd        = "http://www.w3.org/2001/XMLSchema#";
		String rdf        = "http://www.w3.org/1999/02/22-rdf-syntax-ns#";
		String rdfs       = "http://www.w3.org/2000/01/rdf-schema#";
		String nsUTD      = "http://utdallas/semclass#";
		String nsBase     = "http://utdallas/semclass";
		String nsMovie    = nsBase + "/movie#";
		String nsPerson   = nsBase + "/person#";
		String nsBook     = nsBase + "/book#";
		String nsDirector = nsBase + "/director#";
		String nsAuthor   = nsBase + "/author#";
		
		String kubrickURI    = nsDirector + "StanleyKubrick";
		String kubrickFN     = "Stanley Kubrick";
		String kubrickNURI   = nsBase + "/person/StanleyKubrick#name";
		String kubrickGiven  = "Stanley";
		String kubrickFamily = "Kubrick";
		
		String clockworkURI   = nsMovie + "clockworkOrange";
		String clockworkTitle = "A Clockwork Orange";
		String clockworkYear  = "1971";
		String clockworkGenre = "Crime, Drama, Sci-Fi";
		
		String strangeloveURI   = nsMovie + "drStrangelove";
		String strangeloveTitle = "Dr. Strangelove or: How I Learned to Stop Worrying and Love the Bomb";
		String strangeloveYear  = "1964";
		String strangeloveGenre = "Comedy, Drama";
		
		String redAlertURI    = nsBook + "redAlert";
		String redAlertTitle  = "Red Alert";
		String redAlertYear   = "1958";
		
		String georgeURI    = nsAuthor + "peterGeorge";		
		String georgeFN     = "Peter George";
		String georgeNURI   = nsBase + "/person/PeterGeorge#name";
		String georgeGiven  = "Peter";
		String georgeFamily = "George";		
		
		//-------------------------------
		// PART 2
		//-------------------------------
		// Create the in-memory model and supply namespace prefixes
		Model inMemoryModel = ModelFactory.createDefaultModel();			
		inMemoryModel.setNsPrefix("auth", nsAuthor);
		inMemoryModel.setNsPrefix("xsd", xsd);
		inMemoryModel.setNsPrefix("rdf", rdf);
		inMemoryModel.setNsPrefix("rdfs", rdfs);
		inMemoryModel.setNsPrefix("xsd", xsd);
		inMemoryModel.setNsPrefix("base", nsUTD);
		inMemoryModel.setNsPrefix("utd", nsUTD);		
		inMemoryModel.setNsPrefix("movie", nsMovie);
		inMemoryModel.setNsPrefix("person", nsPerson);
		inMemoryModel.setNsPrefix("book", nsBook);
		inMemoryModel.setNsPrefix("director", nsDirector);
		inMemoryModel.setNsPrefix("author", nsAuthor);		
		
		// Create the class hierarchy
		Resource movie = inMemoryModel.createResource(nsMovie);
		Resource person = inMemoryModel.createResource(nsPerson);
		Resource book = inMemoryModel.createResource(nsBook);
		Resource director = inMemoryModel.createResource(nsDirector);
		Resource author = inMemoryModel.createResource(nsAuthor);
		
		movie.addProperty(RDFS.subClassOf, OWL.Thing);
		movie.addProperty(RDF.type, movie);
		person.addProperty(RDFS.subClassOf, OWL.Thing);
		person.addProperty(RDF.type, person);
		book.addProperty(RDFS.subClassOf, OWL.Thing);
		book.addProperty(RDF.type, book);
		director.addProperty(RDFS.subClassOf, person);
		director.addProperty(RDF.type, director);
		author.addProperty(RDFS.subClassOf, person);
		author.addProperty(RDF.type, author);
		
		// Create the different class instances required
		Resource stanleyKubrick     = inMemoryModel.createResource(kubrickURI);
		Resource stanleyKubrickName = inMemoryModel.createResource(kubrickNURI);
		Resource clockworkOrange    = inMemoryModel.createResource(clockworkURI);
		Resource drStrangelove      = inMemoryModel.createResource(strangeloveURI);
		Resource peterGeorge        = inMemoryModel.createResource(georgeURI);
		Resource peterGeorgeName    = inMemoryModel.createResource(georgeNURI);
		Resource redAlert           = inMemoryModel.createResource(redAlertURI);
				
		// Create the custom properties for the classes		
		Property movieTitleProperty = inMemoryModel.createProperty(nsMovie, "title");
		Property movieDebutYearProperty = inMemoryModel.createProperty(nsMovie, "debutYear");
		Property movieGenreProperty = inMemoryModel.createProperty(nsMovie, "genre");
		Property movieDirectedByProperty = inMemoryModel.createProperty(nsDirector, "directedBy");
				
		// Connect properties and classes, popluate data
		
		// Create people
		stanleyKubrick.addProperty(RDF.type, director);
		stanleyKubrick.addProperty(VCARD.FN, kubrickFN);	
		stanleyKubrick.addProperty(VCARD.N, stanleyKubrickName);
		stanleyKubrickName.addProperty(VCARD.Given, kubrickGiven);
		stanleyKubrickName.addProperty(VCARD.Family, kubrickFamily);
		
		peterGeorge.addProperty(RDF.type, author);
		peterGeorge.addProperty(VCARD.FN, georgeFN);	
		peterGeorge.addProperty(VCARD.N, peterGeorgeName);	
		peterGeorge.addProperty(VCARD.Given, georgeGiven);
		peterGeorge.addProperty(VCARD.Family, georgeFamily);
		
		// Create movies
		clockworkOrange.addProperty(RDF.type, movie);
		clockworkOrange.addProperty(movieTitleProperty, clockworkTitle);
		clockworkOrange.addProperty(movieDebutYearProperty, clockworkYear);
		clockworkOrange.addProperty(movieGenreProperty, clockworkGenre);	
		clockworkOrange.addProperty(movieDirectedByProperty, stanleyKubrick);
		
		drStrangelove.addProperty(RDF.type, movie);
		drStrangelove.addProperty(movieTitleProperty, strangeloveTitle);
		drStrangelove.addProperty(movieDebutYearProperty, strangeloveYear);
		drStrangelove.addProperty(movieGenreProperty, strangeloveGenre);	
		drStrangelove.addProperty(movieDirectedByProperty, stanleyKubrick);
		
		// Create books		
		redAlert.addProperty(RDF.type, book);
		redAlert.addProperty(DC.creator, peterGeorge);
		redAlert.addProperty(DC.title, redAlertTitle);
		redAlert.addProperty(DC.date, redAlertYear);
		
		/*
		 * Commented out because the instructions request only the named SDB
		 * model's output.
		 */
		print_results("2", inMemoryModel);
		
		//-------------------------------
		// PART 2-1
		//-------------------------------
		/*System.setProperty("jena.db.user", "jenasdb");
		System.setProperty("jena.db.password", "fastdb");
		
		// Connect to the SDB database using an unnamed Model
		Store store = SDBFactory.connectStore("sdb.ttl");
		Model unnamedSDBModel = SDBFactory.connectDefaultModel(store);
		
		// Clear the database of all previous information
		unnamedSDBModel.removeAll();		
		unnamedSDBModel.setNsPrefix( "nsUTD", nsUTD);
		
		unnamedSDBModel.createResource( seidaURI ) 
			.addProperty(VCARD.FN, fullName)
			.addProperty(VCARD.EMAIL, email)
			.addProperty(VCARD.BDAY, birthday )
			.addProperty(VCARD.TITLE, title)
			.addProperty(VCARD.N,
					unnamedSDBModel.createResource()
						.addProperty(VCARD.Given, fName)
						.addProperty(VCARD.Family, lName)
					);*/

		/*
		 * Commented out because the instructions request only the named SDB
		 * model's output.
		 */
		//print_results("2", unnamedSDBModel);
		
		//unnamedSDBModel.close();	
		
		//-------------------------------
		// PART 2-2
		//-------------------------------	
		// Connect to the SDB database using a named Model
		/*ModelMaker modelMaker = ModelFactory.createMemModelMaker();		
		modelMaker.createModel("myrdf");
		Model namedSDBModel = SDBFactory.connectNamedModel(store, "myrdf");
		
		// Clear the database of all previous information
		namedSDBModel.removeAll();	
		namedSDBModel.setNsPrefix( "nsUTD", nsUTD);
		
		namedSDBModel.createResource( seidaURI ) 
			.addProperty(VCARD.FN, fullName)
			.addProperty(VCARD.EMAIL, email)
			.addProperty(VCARD.BDAY, birthday )
			.addProperty(VCARD.TITLE, title)
			.addProperty(VCARD.N,
					namedSDBModel.createResource()
						.addProperty(VCARD.Given, fName)
						.addProperty(VCARD.Family, lName)
					);
		
		//print_results("2", namedSDBModel);
		
		namedSDBModel.close();	*/		
	}
	
	/*
	 * Prints the contents of model to the output files for this program.
	 * 
	 * @param number -- The section of the lab being printed 
	 * 
	 * @param model -- The model to output the contents of
	 * 
	 * @see Model
	 */
	static void print_results(String number, Model model) {
		try {
			BufferedWriter outXML = new BufferedWriter( 
					new FileWriter( "Lab2_" + number + "_gSteelman.xml" ) 
					);
			model.write( outXML, "RDF/XML");
			outXML.close();
			
			
			// Commented out because the instructions do not request this file format
			
			BufferedWriter outXMLClean = new BufferedWriter( 
					new FileWriter( "Lab2_" + number + "_gSteelman-Clean.xml" ) 
					);
			model.write( outXMLClean, "RDF/XML-ABBREV");
			outXMLClean.close();
						
			
			BufferedWriter outN_TRIPLE = new BufferedWriter( 
					new FileWriter( "Lab2_" + number + "_gSteelman.ntp" ) 
					);
			model.write( outN_TRIPLE, "N-TRIPLE");
			outN_TRIPLE.close();
			
			BufferedWriter outN3 = new BufferedWriter( 
					new FileWriter( "Lab2_" + number + "_gSteelman.n3" ) 
					);			
			model.write( outN3, "N3");			
			outN3.close();			
			
		} catch (IOException e) {			
			System.out.println( "Exception: " );
			System.out.println( e.toString( ) );
		}
	}
}
