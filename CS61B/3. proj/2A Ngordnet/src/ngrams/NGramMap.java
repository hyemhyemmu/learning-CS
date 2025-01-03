package src.ngrams;

import edu.princeton.cs.algs4.In;

import java.util.Collection;
import java.util.HashMap;
import java.util.Map;

import static src.ngrams.TimeSeries.MAX_YEAR;
import static src.ngrams.TimeSeries.MIN_YEAR;

/**
 * An object that provides utility methods for making queries on the
 * Google NGrams dataset (or a subset thereof).
 * <p>
 * An NGramMap stores pertinent data from a "words file" and a "counts
 * file". It is not a map in the strict sense, but it does provide additional
 * functionality.
 *
 * @author Josh Hug
 */
public class NGramMap {
    // these two instance are not supposed to be changed
    private final Map<String, TimeSeries> wordHistories;
    private final TimeSeries totalWordCounts;

    /**
     * Constructs an NGramMap from WORDSFILENAME and COUNTSFILENAME.
     */
    public NGramMap(String wordsFilename, String countsFilename) {
        wordHistories = new HashMap<>();
        totalWordCounts = new TimeSeries();

        loadWordsFile(wordsFilename);
        loadCountsFile(countsFilename);
    }

    /**
     * Provides the history of WORD between STARTYEAR and ENDYEAR, inclusive of both ends. The
     * returned TimeSeries should be a copy, not a link to this NGramMap's TimeSeries. In other
     * words, changes made to the object returned by this function should not also affect the
     * NGramMap. This is also known as a "defensive copy". If the word is not in the data files,
     * returns an empty TimeSeries.
     */
    public TimeSeries countHistory(String word, int startYear, int endYear) {
        validateYearRange(startYear,endYear);
        if (!wordHistories.containsKey(word)) {
            return new TimeSeries();
        }

        return subTimeSeries(word, startYear, endYear);
    }

    /**
     * Provides the history of WORD. The returned TimeSeries should be a copy, not a link to this
     * NGramMap's TimeSeries. In other words, changes made to the object returned by this function
     * should not also affect the NGramMap. This is also known as a "defensive copy". If the word
     * is not in the data files, returns an empty TimeSeries.
     */
    public TimeSeries countHistory(String word) {
        return subTimeSeries(word, MIN_YEAR, MAX_YEAR);

    }

    /**
     * Returns a defensive copy of the total number of words recorded per year in all volumes.
     */
    public TimeSeries totalCountHistory() {
        TimeSeries total = new TimeSeries();
        for (String word : wordHistories.keySet()) {
            TimeSeries wordSeries = wordHistories.get(word);
            for (int year : wordSeries.keySet()) {
                double wordCountInAYear = wordSeries.get(year);
                total.put(year, total.getOrDefault(year, 0.0) + wordCountInAYear);
            }
        }
        return total;
    }

    /**
     * Provides a TimeSeries containing the relative frequency per year of WORD between STARTYEAR
     * and ENDYEAR, inclusive of both ends. If the word is not in the data files, returns an empty
     * TimeSeries.
     */
    public TimeSeries weightHistory(String word, int startYear, int endYear) {
        validateYearRange(startYear,endYear);
        if (!wordHistories.containsKey(word)) {
            return new TimeSeries();
        }
        return wordFrequency(word, startYear, endYear);
    }

    /**
     * Provides a TimeSeries containing the relative frequency per year of WORD compared to all
     * words recorded in that year. If the word is not in the data files, returns an empty
     * TimeSeries.
     */
    public TimeSeries weightHistory(String word) {
        if (!wordHistories.containsKey(word)) {
            return new TimeSeries();
        }
        return wordFrequency(word, MIN_YEAR, MAX_YEAR);
    }

    /**
     * Provides the summed relative frequency per year of all words in WORDS between STARTYEAR and
     * ENDYEAR, inclusive of both ends. If a word does not exist in this time frame, ignore it
     * rather than throwing an exception.
     */
    public TimeSeries summedWeightHistory(Collection<String> words,
                                          int startYear, int endYear) {
        validateYearRange(startYear,endYear);
        TimeSeries result = new TimeSeries();
        for (String word : words) {
            TimeSeries wordFrequency = weightHistory(word, startYear, endYear);
            if (wordFrequency.isEmpty())
                continue;
            for (int year : wordFrequency.keySet()) {
                result.put(year, result.getOrDefault(year, 0.0) + wordFrequency.get(year));
            }
        }
        return result;
    }

    /**
     * Returns the summed relative frequency per year of all words in WORDS. If a word does not
     * exist in this time frame, ignore it rather than throwing an exception.
     */
    public TimeSeries summedWeightHistory(Collection<String> words) {
        return summedWeightHistory(words, MIN_YEAR, MAX_YEAR);
    }

    //helper methods
    private void loadWordsFile(String wordsFilename) {
        In wordsFile = new In(wordsFilename);

        while (wordsFile.hasNextLine()) {
            String line = wordsFile.readLine();
            //use tab to separate into different parts and then put them into one list
            String[] parts = line.split("\t");

            //declare each part
            String word = parts[0];
            int year = Integer.parseInt(parts[1]);
            int count = Integer.parseInt(parts[2]);

            //put them into map
            wordHistories.putIfAbsent(word, new TimeSeries());
            wordHistories.get(word).put(year, (double) count);
        }
    }

    private void loadCountsFile(String countsFilename) {
        In countFile = new In(countsFilename);

        while (countFile.hasNextLine()) {
            String line = countFile.readLine();
            //separate
            String[] parts = line.split(",");

            //process
            int year = Integer.parseInt(parts[0]);
            int count = Integer.parseInt(parts[1]);

            //put
            totalWordCounts.put(year, (double) count);
        }
    }


    private TimeSeries subTimeSeries(String word, int startYear, int endYear) {
        TimeSeries result = new TimeSeries();
        TimeSeries oriTS = wordHistories.get(word);
        for (int year : oriTS.keySet()) {
            if (startYear <= year && year <= endYear) {
                result.put(year, oriTS.get(year));
            }
        }
        return result;
    }

    private TimeSeries wordFrequency(String word, int startYear, int endYear) {
        TimeSeries wordSeries = countHistory(word, startYear, endYear);
        TimeSeries totalSeries = (TimeSeries) totalCountHistory().subMap(startYear, true, endYear, true);
        TimeSeries result = new TimeSeries();

        for (int year : totalSeries.keySet()) {
            Double wordCount = wordSeries.getOrDefault(year, 0.0);
            result.put(year, wordCount / totalSeries.get(year));
        }
        return result;
    }

    private void validateYearRange(int startYear, int endYear) {
        if (startYear > endYear) {
            throw new IllegalArgumentException("Start year must be less than or equal to end year.");
        }
    }

}
