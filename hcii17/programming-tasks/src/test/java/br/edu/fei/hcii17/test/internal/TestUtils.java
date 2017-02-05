package br.edu.fei.hcii17.test.internal;

import java.io.IOException;
import java.nio.file.FileVisitResult;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.SimpleFileVisitor;
import java.nio.file.attribute.AclEntry;
import java.nio.file.attribute.AclEntryPermission;
import java.nio.file.attribute.AclEntryType;
import java.nio.file.attribute.AclFileAttributeView;
import java.nio.file.attribute.BasicFileAttributes;
import java.nio.file.attribute.UserPrincipal;
import java.nio.file.attribute.UserPrincipalLookupService;
import java.util.Arrays;
import java.util.Collections;
import java.util.EnumSet;
import java.util.HashSet;
import java.util.Set;

public class TestUtils {

    private static final Set<AclEntryPermission> ACL_READING_DENIED = EnumSet.of(AclEntryPermission.READ_DATA,
            AclEntryPermission.READ_ATTRIBUTES, AclEntryPermission.DELETE);
    private static Set<AclEntryPermission> ACL_ALL = new HashSet<AclEntryPermission>();
    static {
        Arrays.stream(AclEntryPermission.values()).forEach(p -> ACL_ALL.add(p));
    }

    public static void delete(Path path) {

        if (path == null) {
            return;
        }

        try {
            Files.walkFileTree(path, new SimpleFileVisitor<Path>() {
                @Override
                public FileVisitResult visitFile(Path file, BasicFileAttributes attrs) throws IOException {
                    Files.delete(file);
                    return FileVisitResult.CONTINUE;
                }

                @Override
                public FileVisitResult postVisitDirectory(Path dir, IOException exc) throws IOException {
                    Files.delete(dir);
                    return FileVisitResult.CONTINUE;
                }

            });
        } catch (IOException e) {
        }
    }

    public static Path createTempFile(Path dir, String prefix, String suffix) throws IOException {
        return Files.createTempFile(dir, prefix, suffix);
    }
    
    private static void setAcl(Path path, Set<AclEntryPermission> permissions) {
        try {
            AclFileAttributeView aclAttr = Files.getFileAttributeView(path, AclFileAttributeView.class);
            UserPrincipalLookupService upls = path.getFileSystem().getUserPrincipalLookupService();
            UserPrincipal user = upls.lookupPrincipalByName(System.getProperty("user.name"));
            AclEntry.Builder builder = AclEntry.newBuilder();
            builder.setPermissions(permissions);
            builder.setPrincipal(user);
            builder.setType(AclEntryType.ALLOW);
            aclAttr.setAcl(Collections.singletonList(builder.build()));
        } catch (IOException e) {
        }

    }

    public static void denyReading(Path path) {
        setAcl(path, ACL_READING_DENIED);
    }

    public static void denyExcution(Path path) {
        setAcl(path, ACL_ALL);
    }

    public static String repeat(String str, int times) {

        if (str == null || times <= 0) {
            throw new IllegalArgumentException();
        }

        StringBuffer buffer = new StringBuffer(str.length() * times);
        for (int idx = 0; idx < times; idx++) {
            buffer.append(str);
        }

        return buffer.toString();
    }

}
