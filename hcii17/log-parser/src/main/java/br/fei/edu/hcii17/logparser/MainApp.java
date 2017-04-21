package br.fei.edu.hcii17.logparser;

import java.io.IOException;
import java.net.URISyntaxException;
import java.net.URL;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.Duration;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.concurrent.atomic.LongAdder;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.function.Supplier;
import java.util.stream.Stream;

public class MainApp {

	private static final String LOGFILE = "hcii17-code-assistants-0.log";
	private static final String LOTS_OF_STARS = "-------------------------------------------------------------------------------------------------------------";
	

	/**
	 * Java programming experience.<br />
	 */
	private enum JavaProgrammingExperience {
		INI, INT, ADV;
	}

	/**
	 * Code completion assistant.<br />
	 */
	private enum CodeCompletionAssistant {

		STD("StandardCompletionExtension"), INT("IntelligentCompletionExtension");

		String fullName;

		private CodeCompletionAssistant(String fullName) {
			this.fullName = fullName;
		}

	}

	/**
	 * Task representation.<br />
	 */
	static abstract class Task {

		String id;
		LocalTime start;
		LocalTime end;
		Duration duration;
		CodeCompletionAssistant codeCompletionAssistant;
		List<String> proposals;

		public Task(String name, CodeCompletionAssistant codeCompletionAssistant, String starts, String ends) {
			super();
			this.id = name;
			this.codeCompletionAssistant = codeCompletionAssistant;
			this.start = LocalTime.parse(starts);
			this.end = LocalTime.parse(ends);
			this.duration = Duration.between(start, end);
			this.proposals = new ArrayList<String>();
		}

		protected void addExpectedProposals(String... strings) {
			this.proposals.addAll(Arrays.asList(strings));
		}
	}

	static class Task01 extends Task {
		public Task01(CodeCompletionAssistant codeCompletionAssistant, String starts, String ends) {
			super("01", codeCompletionAssistant, starts, ends);
			addExpectedProposals("from : Path", "to : Path", "toFile()", "isDirectory()", "Files - java.nio.file",
					"walkFileTree(Path start, FileVisitor<? super Path> visitor)");
		}
	}

	static class Task02 extends Task {
		public Task02(CodeCompletionAssistant codeCompletionAssistant, String starts, String ends) {
			super("02", codeCompletionAssistant, starts, ends);
			addExpectedProposals("start : LocalDateTime", "end : LocalDateTime",
					"isAfter(ChronoLocalDateTime<?> other)", "isBefore(ChronoLocalDateTime<?> other)",
					"LocalDateTime - java.time", "now()", "ChronoUnit - java.time",
					"until(Temporal endExclusive, TemporalUnit unit)", "SECONDS", "Duration - java.time",
					"between(Temporal startInclusive, Temporal endExclusive)", "getSeconds()");
		}
	}

	static class Task03 extends Task {
		public Task03(CodeCompletionAssistant codeCompletionAssistant, String starts, String ends) {
			super("03", codeCompletionAssistant, starts, ends);
			addExpectedProposals("stream : Stream", "stream()", "filter(Predicate<? super String> arg0)",
					"map(Function<? super String,? extends R> mapper)", "sorted()");
		}
	}

	static class Participant {
		String id;
		JavaProgrammingExperience exp;
		List<Task> tasks = new ArrayList<Task>();

		public Participant(String id, JavaProgrammingExperience exp, Task... tasks) {
			super();
			this.id = id;
			this.exp = exp;
			this.tasks.addAll(Arrays.asList(tasks));
		}

	}

	// participants time log
	static List<Participant> participants = new ArrayList<Participant>();
	static {
		participants.add(new Participant("01", JavaProgrammingExperience.ADV,
				new Task01(CodeCompletionAssistant.STD, "20:18:08", "21:16:39"),
				new Task02(CodeCompletionAssistant.INT, "21:20:28", "21:57:14"),
				new Task03(CodeCompletionAssistant.INT, "22:01:58", "22:17:12")));
		participants.add(new Participant("02", JavaProgrammingExperience.INT,
				new Task01(CodeCompletionAssistant.INT, "20:10:26", "20:18:49"),
				new Task02(CodeCompletionAssistant.INT, "19:50:34", "20:02:05"),
				new Task03(CodeCompletionAssistant.STD, "20:04:10", "20:07:55")));
		participants.add(new Participant("03", JavaProgrammingExperience.ADV,
				new Task01(CodeCompletionAssistant.STD, "19:49:28", "20:15:07"),
				new Task02(CodeCompletionAssistant.INT, "20:19:46", "20:53:40"),
				new Task03(CodeCompletionAssistant.INT, "19:33:47", "19:43:36")));
		participants.add(new Participant("04", JavaProgrammingExperience.ADV,
				new Task01(CodeCompletionAssistant.STD, "19:54:33", "20:25:52"),
				new Task02(CodeCompletionAssistant.INT, "20:28:53", "20:41:11"),
				new Task03(CodeCompletionAssistant.INT, "20:44:54", "20:55:05")));
		participants.add(new Participant("05", JavaProgrammingExperience.ADV,
				new Task01(CodeCompletionAssistant.INT, "20:58:33", "21:09:37"),
				new Task02(CodeCompletionAssistant.INT, "19:54:52", "20:38:05"),
				new Task03(CodeCompletionAssistant.STD, "20:40:38", "20:55:07")));
		participants.add(new Participant("06", JavaProgrammingExperience.INT,
				new Task01(CodeCompletionAssistant.INT, "20:08:41", "21:51:05"),
				new Task02(CodeCompletionAssistant.STD, "21:54:17", "22:26:27"),
				new Task03(CodeCompletionAssistant.INT, "19:55:38", "20:03:29")));
		participants.add(new Participant("07", JavaProgrammingExperience.INT,
				new Task01(CodeCompletionAssistant.INT, "19:57:09", "20:59:38"),
				new Task02(CodeCompletionAssistant.INT, "21:02:00", "21:25:41"),
				new Task03(CodeCompletionAssistant.INT, "21:28:34", "21:34:47")));
		participants.add(new Participant("08", JavaProgrammingExperience.INI,
				new Task01(CodeCompletionAssistant.INT, "21:39:36", "22:27:15"),
				new Task02(CodeCompletionAssistant.INT, "19:56:57", "21:04:43"),
				new Task03(CodeCompletionAssistant.STD, "21:11:33", "21:34:41")));
		participants.add(new Participant("09", JavaProgrammingExperience.ADV,
				new Task01(CodeCompletionAssistant.INT, "20:24:46", "21:19:03"),
				new Task02(CodeCompletionAssistant.STD, "21:24:36", "22:18:28"),
				new Task03(CodeCompletionAssistant.INT, "20:04:02", "20:18:52")));
	}

	private static void log(Object obj) {
		System.out.println(obj);
	}

	/**
	 * Entry point.<br />
	 * 
	 * @param args
	 * @throws Exception
	 */
	public static void main(String[] args) throws Exception {

		Map<String, Long> activationMap = new HashMap<String, Long>();
		Map<CodeCompletionAssistant, Long> activationsPerAssistantMap = new HashMap<CodeCompletionAssistant, Long>();

		Map<String, Long> suggestionsMap = new HashMap<String, Long>();
		Map<CodeCompletionAssistant, Long> suggestionsPerAssistantMap = new HashMap<CodeCompletionAssistant, Long>();

		Map<String, Map<String, Long>> proposals = new HashMap<String, Map<String, Long>>();

		log("\r\nParticipants activations per task");
		log(LOTS_OF_STARS);
		log("(1)\t(2)\t(3)\t(4)\t(5)\t(6)\t  \t(7) \t  \t(8) \t  \t  \t(9) \t(10)");
		log("ID \tExp\tTsk\tDur\tAst\tAct\tDT\tAvgDT\tP\tAvgP\tAP\tCP\tAPR \tCPR");
		log(LOTS_OF_STARS);
		
		participants.forEach(participant -> {

			try {

				final URL url = MainApp.class.getResource("/logs/" + participant.id + "/" + LOGFILE);
				if (url == null) {
					return;
				}

				final Path path = Paths.get(url.toURI());
				participant.tasks.forEach(task -> {

					final String assistant = task.codeCompletionAssistant.fullName;

					Supplier<Stream<String>> supplier = () -> {
						Stream<String> stream = null;
						try {
							stream = Files.lines(path).filter(new Predicate<String>() {
								@Override
								public boolean test(String arg0) {
									boolean keep = false;
									if (arg0.length() > 20) {
										int s = arg0.indexOf(" ", 8) + 1;
										int e = arg0.indexOf(",");
										if (s > 1 && e > 0 && e > s) {
											LocalTime instant = LocalTime.parse(arg0.substring(s, e));
											keep = instant.isAfter(task.start.minusMinutes(1))
													&& instant.isBefore(task.end.plusMinutes(1));
										}
									}
									return keep;
								}
							}).filter(l -> l.contains(assistant));
						} catch (IOException e) {
						}
						return stream;
					};

					// activations
					Stream<String> callsStream = supplier.get().filter(l -> l.contains("active"));
					final long activations = callsStream.count();
					activationMap.compute(task.id, (k, v) -> (v == null) ? activations : v + activations);
					activationsPerAssistantMap.compute(task.codeCompletionAssistant,
							(k, v) -> (v == null) ? activations : v + activations);

					// activations time
					Stream<Long> displayTimeStream = supplier.get().filter(l -> l.contains("active"))
							.map(new Function<String, Long>() {
								@Override
								public Long apply(String t) {
									return Long.parseLong(
											t.substring(t.indexOf(" for ") + 5, t.indexOf("seconds")).trim());
								}
							});
					LongAdder displayTimeAdder = new LongAdder();
					displayTimeStream.forEach(displayTimeAdder::add);
					final long displayTime = displayTimeAdder.sum();

					// proposals
					Stream<Long> completionsStream = supplier.get().filter(l -> l.contains("completion proposals"))
							.map(new Function<String, Long>() {
								@Override
								public Long apply(String t) {
									return Long.parseLong(
											t.substring(t.indexOf(" are ") + 5, t.indexOf("completion")).trim());
								}
							});
					LongAdder completionsAdder = new LongAdder();
					completionsStream.forEach(completionsAdder::add);
					final long completions = completionsAdder.sum();

					suggestionsMap.compute(task.id, (k, v) -> (v == null) ? completions : v + completions);
					suggestionsPerAssistantMap.compute(task.codeCompletionAssistant,
							(k, v) -> (v == null) ? completions : v + completions);

					supplier.get().filter(l -> l.contains("Applied")).map(new Function<String, String>() {
						@Override
						public String apply(String t) {
							return t.substring(t.indexOf("'") + 1, t.lastIndexOf("'")).trim();
						}
					}).forEach(p -> {
						Map<String, Long> statsMap = proposals.get(task.id);
						if (statsMap == null) {
							statsMap = new HashMap<String, Long>();
						}
						statsMap.compute(p, (k, v) -> ((v == null) ? 1 : v + 1));
						proposals.put(task.id, statsMap);
					});

					// applied proposals
					final long appliedProposals = supplier.get().filter(l -> l.contains("Applied")).count();

					// unrelated proposals
					List<Long> tmpList = new ArrayList<Long>();
					task.proposals.forEach(s -> {
						tmpList.add(supplier.get().filter(l -> l.contains("'" + s)).count());
					});
					LongAdder a = new LongAdder();
					tmpList.stream().forEach(a::add);
					final long contribSug = a.sum();

					log(String.format("%s\t%s\t%s\t%d\t%s\t%d\t%d\t%3.2f\t%d\t%3.2f\t%d\t%d\t%3.2f\t%3.2f",
							participant.id, participant.exp.name(), task.id, task.duration.getSeconds(),
							task.codeCompletionAssistant.name(), activations, displayTime,
							(displayTime / (activations * 1.0f)), completions, (completions / (activations * 1.0f)),
							appliedProposals, contribSug, (appliedProposals / (activations * 1.0f)) * 100,
							(contribSug / (appliedProposals * 1.0f)) * 100));

				});
			} catch (URISyntaxException e) {
			}
		});
		log(LOTS_OF_STARS);

		log("\r\nOverall activations per task");
		activationMap.forEach((k, v) -> log(String.format("%s\t%d", k, v)));
		log("\r\nOverall activations per assistant");
		activationsPerAssistantMap.forEach((k, v) -> log(String.format("%s\t%d", k, v)));

		log("\r\nOverall suggestions per task");
		suggestionsMap.forEach((k, v) -> log(String.format("%s\t%d\t%f", k, v, (v / (activationMap.get(k) * 1.0f)))));
		log("\r\nOverall suggestions per assistant");
		suggestionsPerAssistantMap.forEach(
				(k, v) -> log(String.format("%s\t%d\t%f", k, v, (v / (activationsPerAssistantMap.get(k) * 1.0f)))));

		log("\r\nTop10 suggestions per task");
		proposals.forEach((k1, v1) -> {
			log(String.format("Task: %s", k1));

			LongAdder a = new LongAdder();
			v1.values().stream().forEach(a::add);
			final long overall = a.sum();

			v1.entrySet().stream().sorted(Map.Entry.comparingByValue(Collections.reverseOrder())).limit(10)
					.forEach(e -> {
						final long count = e.getValue();
						log(String.format("%d\t%3.2f\t%s", count, (count / (overall * 1.0f)) * 100f, e.getKey()));
					});
		});

	}

}
